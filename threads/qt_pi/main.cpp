#include <QCoreApplication>
#include <QThread>

constexpr static int N = 1e7;

constexpr double from = 0.;
constexpr double to = 1.;
constexpr double dx = (to - from) / static_cast<double>(N);

constexpr double f(double x)
{
    return sqrt(1 - x * x);
}

class PiThread : public QThread {
public:
    PiThread(int i, int n) : QThread(), m_rank(i), m_size(n) {}
    double result() const { return m_result; }
private:
    void run() override {
        m_result = 0;
        for(int i = m_rank; i < N; i += m_size) {
            const double x = from + i * dx;
            const double fx = f(x);
            m_result += fx * dx;
        }
    }
    int m_rank;
    int m_size;
    double m_result;
};

int main(int argc, char *argv[])
{
    constexpr int n = 4;

    QList<PiThread*> threads;
    for (int i = 0; i < n; i++) {
        threads.append(new PiThread(i, n));
        threads.last()->start();
    }

    double sum = 0;
    for (int i = 0; i < n; i++) {
        threads[i]->wait();
        sum += threads[i]->result();
    }

    qDebug() << 4 * sum;

    while(!threads.isEmpty())
        delete threads.takeFirst();

}
