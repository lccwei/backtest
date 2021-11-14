#ifndef MYAXISTICKERTEXT_H
#define MYAXISTICKERTEXT_H

#include "qcustomplot.h"

class MyAxisTickerText : public QCPAxisTickerText {
protected:
    virtual QVector<double> createTickVector(double tickStep,
                                             const QCPRange& range) Q_DECL_OVERRIDE {
        Q_UNUSED(tickStep)
        QVector<double> result;
        if (mTicks.isEmpty())
            return result;

        auto start = mTicks.lowerBound(range.lower);
        auto end = mTicks.upperBound(range.upper);
        if (start != mTicks.constBegin())
            --start;
        if (end != mTicks.constEnd())
            ++end;

        int count = cleanMantissa(std::distance(start, end) / double(mTickCount + 1e-10));

        auto it = start;
        while (it != end) {
            result.append(it.key());
            int step = count;
            if (step == 0)
                ++it;
            while (--step >= 0 && it != end)
                ++it;
        }

        return result;
    }
};

#endif  // MYAXISTICKERTEXT_H
