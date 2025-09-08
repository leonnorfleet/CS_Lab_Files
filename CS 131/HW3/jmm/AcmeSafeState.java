import java.util.concurrent.locks.ReentrantLock;

class AcmeSafeState implements State {
    private long[] value;

    private ReentrantLock l = new ReentrantLock();

    AcmeSafeState(int length) { value = new long[length]; }

    public int size() { return value.length; }

    public long[] current() { return value; }

    public void swap(int i, int j) {
        l.lock();
        value[i]--;
        value[j]++;
        l.unlock();
    }
}