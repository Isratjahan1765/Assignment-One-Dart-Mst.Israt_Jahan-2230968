public class Main {
    private static final int NUM_PHILOSOPHERS = 5;

    public static void main(String[] args) {
        DiningServer server = new DiningServerImpl();

        // Create and start philosopher threads
        Thread[] philosophers = new Thread[NUM_PHILOSOPHERS];
        for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
            philosophers[i] = new Thread(new Philosopher(i, server));
            philosophers[i].start();
        }

        System.out.println("Dining Philosophers simulation started. Press Ctrl+C to stop.");
    }
}
