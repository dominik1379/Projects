package sk.tuke.kpi.kp.bejeweled.core;

public class Timer {
    private int time;
    private boolean running;
    private Thread timerThread;

    public Timer() {
        this.time = 0;
        this.running = false;
    }

    //Metoda pre start casovacu
    public void start() {
        if (running){
            return;
        }
        running = true;

        timerThread = new Thread(() -> {
            while (running) {
                Second();
                time++;
            }
        });

        timerThread.setDaemon(true);
        timerThread.start();
    }

    //Metoda na spravne fungovanie sekund
    private void Second() {
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    //Metoda na zastavenie casovacu
    public void stop() {
        running = false;
        if (timerThread != null) {
            timerThread.interrupt();
            try {
                timerThread.join();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }

    public int getTime() {
        return time;
    }

}
