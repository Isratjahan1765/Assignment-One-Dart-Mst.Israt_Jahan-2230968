import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class DiningServerImpl implements DiningServer {
    private static final int NUM_PHILOSOPHERS = 5;

    // States for philosophers
    private static final int THINKING = 0;
    private static final int HUNGRY = 1;
    private static final int EATING = 2;

    // The shared state of all philosophers
    private int[] philosopherStates;

    // A single lock to protect the shared 'philosopherStates' array
    // and to manage the condition variables. This acts as the monitor lock.
    private final ReentrantLock monitorLock; // Declared as final and initialized in constructor

    // Condition variables for each philosopher to wait on
    private Condition[] canEat;

    public DiningServerImpl() {
        philosopherStates = new int[NUM_PHILOSOPHERS];
        monitorLock = new ReentrantLock(); // Correctly initialized here
        canEat = new Condition[NUM_PHILOSOPHERS];

        for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
            philosopherStates[i] = THINKING; // All start thinking
            canEat[i] = monitorLock.newCondition(); // Each philosopher waits on their own condition
        }
    }

    // Helper method to check if a philosopher 'i' can eat
    // This method must be called while holding the monitorLock
    private boolean canPhilosopherEat(int i) {
        // A philosopher can eat if they are HUNGRY AND
        // their left and right neighbors are NOT EATING.
        // Left neighbor: (i + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
        // Right neighbor: (i + 1) % NUM_PHILOSOPHERS
        return philosopherStates[i] == HUNGRY &&
               philosopherStates[(i + NUM_PHILOSOPHERS - 1 + NUM_PHILOSOPHERS) % NUM_PHILOSOPHERS] != EATING && // Added +NUM_PHILOSOPHERS to handle negative results from %
               philosopherStates[(i + 1) % NUM_PHILOSOPHERS] != EATING;
    }

    @Override
    public void takeForks(int philosopherNumber) {
        monitorLock.lock(); // Acquire the monitor lock
        try {
            philosopherStates[philosopherNumber] = HUNGRY; // Set state to Hungry
            System.out.println("Philosopher " + philosopherNumber + " is Hungry.");

            // While the philosopher cannot eat, wait
            while (!canPhilosopherEat(philosopherNumber)) {
                try {
                    canEat[philosopherNumber].await(); // Wait on this philosopher's condition
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    return; // Exit if interrupted
                }
            }

            // If we reach here, the philosopher can eat
            philosopherStates[philosopherNumber] = EATING; // Set state to Eating
            System.out.println("Philosopher " + philosopherNumber + " is Eating.");

        } finally {
            monitorLock.unlock(); // Release the monitor lock
        }
    }

    @Override
    public void returnForks(int philosopherNumber) {
        monitorLock.lock(); // Acquire the monitor lock
        try {
            philosopherStates[philosopherNumber] = THINKING; // Set state to Thinking
            System.out.println("Philosopher " + philosopherNumber + " is Thinking.");

            // After putting down forks, check if neighbors can now eat
            int leftNeighbor = (philosopherNumber + NUM_PHILOSOPHERS - 1 + NUM_PHILOSOPHERS) % NUM_PHILOSOPHERS; // Ensure positive index
            int rightNeighbor = (philosopherNumber + 1) % NUM_PHILOSOPHERS;

            // Signal left neighbor if they are hungry and can now eat
            if (canPhilosopherEat(leftNeighbor)) {
                canEat[leftNeighbor].signal();
            }
            // Signal right neighbor if they are hungry and can now eat
            if (canPhilosopherEat(rightNeighbor)) {
                canEat[rightNeighbor].signal();
            }

        } finally {
            monitorLock.unlock(); // Release the monitor lock
        }
    }
}


