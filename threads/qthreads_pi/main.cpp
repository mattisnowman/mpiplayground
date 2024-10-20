#include <QCoreApplication>
#include <QThread>
#include <QMutex>
#include <QTime>

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
    PiThread(int i, int n, double *result, QMutex *mutex) :
        QThread(), m_rank(i), m_size(n), m_result(result), m_mutex(mutex) {}
private:


    void run() override {
        double result = 0;
        for(int i = m_rank; i < N; i += m_size) {
            const double x = from + i * dx;
            const double fx = f(x);
            *m_result += fx * dx;
        }
    }


    int m_rank;
    int m_size;
    double *m_result;
    QMutex *m_mutex;

};

int main(int argc, char *argv[])
{
    constexpr int size = 8;

    QMutex mutex;
    double sum = 0;
    QList<PiThread*> threads;


    for (int i = 0; i < size; i++)
        threads << new PiThread(i, size, &sum, &mutex);

    auto begin = QTime::currentTime();

    for (auto t : threads)
        t->start();

    for (auto t : threads)
        t->wait();

    auto end = QTime::currentTime();

    qDebug().nospace() << "Processes = " << size << ", Exec. duration = "
             << begin.msecsTo(end) / 1000.
             << "s, PI = " << 4 * sum << ", error = "  << 4 * sum - M_PI << Qt::endl;

    while(!threads.isEmpty())
        delete threads.takeFirst();

}
