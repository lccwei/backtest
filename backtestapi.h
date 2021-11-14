#ifndef BACKTESTAPI_H
#define BACKTESTAPI_H

#include <QObject>
#include <QtCore/QDate>
#include <QtCore/QtGlobal>
#include <QtCore/QObject>
#include <QtCore/QVariant>

#define BACKTESTSERVER_PORT "backtestserver/port"
#define BACKTESTSERVER_PROGRESS_PATH "backtestserver/progress_path"
#define BACKTESTSERVER_RESULT_PATH "backtestserver/result_path"
#define BACKTESTSERVER_PROGRESS_HEADER "backtest_progress"

namespace LiteApi {
class IOrder : public QObject {

    Q_OBJECT
    Q_PROPERTY(QString code READ code WRITE setCode)
    Q_PROPERTY(qint64 trade_time READ tradeTime WRITE setTradeTime)
    Q_PROPERTY(qint64 close_time READ closeTime WRITE setCloseTime)
    Q_PROPERTY(qint64 volume READ volume WRITE setVolume)
    Q_PROPERTY(qint64 matched_vol READ matchedVol WRITE setMatchedVol)
    Q_PROPERTY(qreal price READ price WRITE setPrice)
    Q_PROPERTY(qint8 ord_type READ ordType WRITE setOrdType)
    Q_PROPERTY(qint8 exec_type READ execType WRITE setExecType)
    Q_PROPERTY(qint8 status READ status WRITE setStatus)
    Q_PROPERTY(qint8 cmd READ cmd WRITE setCmd)

public:
    IOrder(QObject* parent = 0) : QObject(parent){};

    IOrder(const IOrder& order) {
        copy(order);
    }

    IOrder& operator=(const IOrder& r) {
        copy(r);
        return *this;
    }

    void copy(const IOrder& order) {
        setCode(order.code());
        setTradeTime(order.tradeTime());
        setTradeTime(order.closeTime());
        setVolume(order.volume());
        setMatchedVol(order.matchedVol());
        setPrice(order.price());
        setOrdType(order.ordType());
        setExecType(order.execType());
        setStatus(order.status());
        setCmd(order.cmd());
    }

    const QString& code() const {
        return m_code;
    }
    void setCode(const QString& code) {
        m_code = code;
    }

    qint64 tradeTime() const {
        return m_tradeTime;
    }
    void setTradeTime(qint64 time) {
        m_tradeTime = time;
    }

    qint64 closeTime() const {
        return m_closeTime;
    }
    void setCloseTime(qint64 time) {
        m_closeTime = time;
    }

    qint64 volume() const {
        return m_volume;
    }
    void setVolume(qint64 vol) {
        m_volume = vol;
    }

    qint64 matchedVol() const {
        return m_matchedVol;
    }
    void setMatchedVol(qint64 vol) {
        m_matchedVol = vol;
    }

    qreal price() const {
        return m_price;
    }
    void setPrice(qreal price) {
        m_price = price;
    }

    qint8 ordType() const {
        return m_ordType;
    }
    void setOrdType(qint8 type) {
        m_ordType = type;
    }

    qint8 execType() const {
        return m_execType;
    }
    void setExecType(qint8 type) {
        m_execType = type;
    }

    qint8 status() const {
        return m_status;
    }
    void setStatus(qint8 status) {
        m_status = status;
    }

    qint8 cmd() const {
        return m_execType;
    }
    void setCmd(qint8 type) {
        m_execType = type;
    }

private:
    QString m_code;
    qint64 m_tradeTime;
    qint64 m_closeTime;   // 订单完结时间
    qint64 m_volume;      // 数量
    qint64 m_matchedVol;  // 当前已成
    qreal m_price;        // 订单价格，成交价格需要结合 E_ExecType
    qint8 m_ordType;      // 订单类型: E_OrderType
    qint8 m_execType;     // 订单的价格类型:E_ExecType
    qint8 m_status;       // 订单状态：初始直接为已报
    qint8 m_cmd;          // 订单方向 E_OrderCmd
};

class IPosition : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString code READ code WRITE setCode)
    Q_PROPERTY(qint64 close_time READ closeTime WRITE setCloseTime)
    Q_PROPERTY(qreal amount READ amount WRITE setAmount)
    Q_PROPERTY(qint64 hold_vol READ holdVol WRITE setHoldVol)
    Q_PROPERTY(qreal commisions READ commisions WRITE setCommisions)

public:
    IPosition(QObject* parent = 0) : QObject(parent){};

    IPosition(const IPosition& pos) {
        copy(pos);
    }

    IPosition& operator=(const IPosition& r) {
        copy(r);
        return *this;
    }

    void copy(const IPosition& pos) {
        setCode(pos.code());
        setCloseTime(pos.closeTime());
        setAmount(pos.amount());
        setHoldVol(pos.holdVol());
        setCommisions(pos.commisions());
    }

    const QString& code() const {
        return m_code;
    }
    void setCode(const QString& code) {
        m_code = code;
    }

    qint64 closeTime() const {
        return m_closeTime;
    }
    void setCloseTime(qint64 time) {
        m_closeTime = time;
    }

    qreal amount() const {
        return m_amount;
    }
    void setAmount(qint64 amount) {
        m_amount = amount;
    }

    qint64 holdVol() const {
        return m_holdVol;
    }
    void setHoldVol(qint64 vol) {
        m_holdVol = vol;
    }

    qreal commisions() const {
        return m_commisions;
    }
    void setCommisions(qint64 commisions) {
        m_commisions = commisions;
    }

private:
    QString m_code;
    qint64 m_closeTime;  // 此刻的收盘price，可计算浮盈亏
    qreal m_amount;      // 持仓金额
    qint64 m_holdVol;  // 持仓方向，直接使用hold_vol的正负判断多空, 当前持仓量（不会计算左仓）
    qreal m_commisions;  // 费用（累加）
};

class ITradeStat : public QObject {
    Q_OBJECT
    Q_PROPERTY(qint32 trade_cnt READ tradeCnt WRITE setTradeCnt)
    Q_PROPERTY(qint32 trade_day_cnt READ tradeDayCnt WRITE setTradeDayCnt)
    Q_PROPERTY(qint32 order_cnt READ orderCnt WRITE setOrderCnt)
    Q_PROPERTY(qint32 finished_order_cnt READ finishedOrderCnt WRITE setFinishedOrderCnt)
    Q_PROPERTY(qint32 history_position_cnt READ historyPositionCnt WRITE setHistoryPositionCnt)
    Q_PROPERTY(qint32 last_position_cnt READ lastPositionCnt WRITE setLastPositionCnt)
    Q_PROPERTY(qreal cash_beg READ cashBeg WRITE setCashBeg)
    Q_PROPERTY(qreal cash_end READ cashEnd WRITE setCashEnd)
    Q_PROPERTY(qreal pos_asset READ posAsset WRITE setPosAsset)
    Q_PROPERTY(qreal abs_rtn READ absRtn WRITE setAbsRtn)
    Q_PROPERTY(qreal tot_rtn READ totRtn WRITE setTotRtn)
    Q_PROPERTY(qreal anual_rtn READ anualRtn WRITE setAnualRtn)
    Q_PROPERTY(qreal rel_rtn READ relRtn WRITE setRelRtn)
    Q_PROPERTY(qreal d_alpha READ alpha WRITE setAlpha)
    Q_PROPERTY(qreal d_beta READ beta WRITE setBeta)
    Q_PROPERTY(qreal rtn_wave READ rtnWave WRITE setRtnWave)
    Q_PROPERTY(qreal d_sharp READ sharp WRITE setSharp)
    Q_PROPERTY(qreal info_rto READ infoRto WRITE setInfoRto)
    Q_PROPERTY(qreal max_drawdown READ maxDrawdown WRITE setMaxDrawdown)

public:
    ITradeStat(QObject* parent = 0) : QObject(parent){};

    ITradeStat(const ITradeStat& stat) {
        copy(stat);
    }

    ITradeStat& operator=(const ITradeStat& r) {
        copy(r);
        return *this;
    }

    void copy(const ITradeStat& stat) {
        setTradeCnt(stat.tradeCnt());
        setTradeDayCnt(stat.tradeDayCnt());
        setOrderCnt(stat.orderCnt());
        setFinishedOrderCnt(stat.finishedOrderCnt());
        setHistoryPositionCnt(stat.historyPositionCnt());
        setLastPositionCnt(stat.lastPositionCnt());
        setCashBeg(stat.cashBeg());
        setCashEnd(stat.cashEnd());
        setPosAsset(stat.posAsset());
        setAbsRtn(stat.absRtn());
        setTotRtn(stat.totRtn());
        setAnualRtn(stat.anualRtn());
        setRelRtn(stat.relRtn());
        setAlpha(stat.alpha());
        setBeta(stat.beta());
        setRtnWave(stat.rtnWave());
        setSharp(stat.sharp());
        setInfoRto(stat.infoRto());
        setMaxDrawdown(stat.maxDrawdown());
    }

    qint32 tradeCnt() const {
        return m_tradeCnt;
    }
    void setTradeCnt(qint32 cnt) {
        m_tradeCnt = cnt;
    }

    qint32 tradeDayCnt() const {
        return m_tradeDayCnt;
    }
    void setTradeDayCnt(qint32 cnt) {
        m_tradeDayCnt = cnt;
    }

    qint32 orderCnt() const {
        return m_orderCnt;
    }
    void setOrderCnt(qint32 cnt) {
        m_orderCnt = cnt;
    }

    qint32 finishedOrderCnt() const {
        return m_finishedOrderCnt;
    }
    void setFinishedOrderCnt(qint32 cnt) {
        m_finishedOrderCnt = cnt;
    }

    qint32 historyPositionCnt() const {
        return m_historyPositionCnt;
    }
    void setHistoryPositionCnt(qint32 cnt) {
        m_historyPositionCnt = cnt;
    }

    qint32 lastPositionCnt() const {
        return m_lastPositionCnt;
    }
    void setLastPositionCnt(qint32 cnt) {
        m_lastPositionCnt = cnt;
    }

    qreal cashBeg() const {
        return m_cashBeg;
    }
    void setCashBeg(qreal cash) {
        m_cashBeg = cash;
    }

    qreal cashEnd() const {
        return m_cashEnd;
    }
    void setCashEnd(qreal cash) {
        m_cashEnd = cash;
    }

    qreal posAsset() const {
        return m_posAsset;
    }
    void setPosAsset(qreal asset) {
        m_posAsset = asset;
    }

    qreal absRtn() const {
        return m_absRtn;
    }
    void setAbsRtn(qreal rtn) {
        m_absRtn = rtn;
    }

    qreal totRtn() const {
        return m_totRtn;
    }
    void setTotRtn(qreal rtn) {
        m_totRtn = rtn;
    }

    qreal anualRtn() const {
        return m_anualRtn;
    }
    void setAnualRtn(qreal rtn) {
        m_anualRtn = rtn;
    }

    qreal relRtn() const {
        return m_relRtn;
    }
    void setRelRtn(qreal rtn) {
        m_relRtn = rtn;
    }

    qreal alpha() const {
        return m_alpha;
    }
    void setAlpha(qreal alpha) {
        m_alpha = alpha;
    }

    qreal beta() const {
        return m_beta;
    }
    void setBeta(qreal beta) {
        m_beta = beta;
    }

    qreal rtnWave() const {
        return m_rtnWave;
    }
    void setRtnWave(qreal rtnWave) {
        m_rtnWave = rtnWave;
    }

    qreal sharp() const {
        return m_sharp;
    }
    void setSharp(qreal sharp) {
        m_sharp = sharp;
    }

    qreal infoRto() const {
        return m_infoRto;
    }
    void setInfoRto(qreal infoRto) {
        m_infoRto = infoRto;
    }

    qreal maxDrawdown() const {
        return m_maxDrawdown;
    }
    void setMaxDrawdown(qreal maxDrawdown) {
        m_maxDrawdown = maxDrawdown;
    }

private:
    qint32 m_tradeCnt;            // 总的交易时间片
    qint32 m_tradeDayCnt;         // 总交易日
    qint32 m_orderCnt;            // 历史合计总订单数量
    qint32 m_finishedOrderCnt;    // 已完结订单数量
    qint32 m_historyPositionCnt;  // 历史合计总持仓（根据标的统计）
    qint32 m_lastPositionCnt;     // 最后持仓数量
    qreal m_cashBeg;              // 起始时候的cash
    qreal m_cashEnd;              // 终结时候的cash
    qreal m_posAsset;             // 终结的持仓资产
    qreal m_absRtn;               // 绝对收益率
    qreal m_totRtn;               // 累计收益率
    qreal m_anualRtn;             // 年化收益
    qreal m_relRtn;               // 相对收益率
    qreal m_alpha;
    qreal m_beta;
    qreal m_rtnWave;      // 收益波动率
    qreal m_sharp;        // 夏普比率
    qreal m_infoRto;      // 信息比率
    qreal m_maxDrawdown;  // 最大回撤
};

struct IBackTtestResult {
    QList<IOrder> orders;
    QMap<QString, IPosition> positions;
    ITradeStat stat;
    qint64 timems;
};

class IBackTestServer : public QObject {
    Q_OBJECT
public:
    IBackTestServer(QObject* parent) : QObject(parent) {}

    virtual const QString& progressPath() const = 0;
    virtual const QString& resultPath() const = 0;
    virtual const qint32& port() const = 0;
    virtual QList<IBackTtestResult> getResults() = 0;
    virtual qint32 listen() = 0;
signals:
    void progress(float);
    void result(const QString&);
};

}  // namespace LiteApi

#endif  // BACKTESTAPI_H
