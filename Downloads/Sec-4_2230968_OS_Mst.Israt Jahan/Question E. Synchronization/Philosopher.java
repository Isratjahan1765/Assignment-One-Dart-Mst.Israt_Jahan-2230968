import java.util.Random;

public class Philosopher implements Runnable {
    private int id;
    private DiningServer server;
    private Random random;

    public Philosopher(int id, DiningServer server) {
        this.id = id;
        this.server = server;
        this.random = new Random();
    }

    @Override
    public void run() {
        try {
            while (true) {
                // 1. Thinking State
                System.out.println("Philosopher " + id + " is Thinking.");
                Thread.sleep(random.nextInt(3000) + 1000); // Think for 1-4 seconds

                // 2. Hungry State (implicitly handled by takeForks)
                server.takeForks(id); // Attempts to acquire forks

                // 3. Eating State
                Thread.sleep(random.nextInt(3000) + 1000); // Eat for 1-4 seconds

                // 4. Return Forks
                server.returnForks(id); // Releases forks

                // Loop continues
            }
        } catch (InterruptedException e) {
            System.out.println("Philosopher " + id + " interrupted and stopped.");
            Thread.currentThread().interrupt();
        }
    }
}




