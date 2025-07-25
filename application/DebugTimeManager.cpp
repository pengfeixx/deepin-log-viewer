// SPDX-FileCopyrightText: 2019 - 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "DebugTimeManager.h"
#include <QDateTime>
#include <QDebug>
#include <QLoggingCategory>

#include <sys/time.h>
#include <time.h>

Q_DECLARE_LOGGING_CATEGORY(logApp)

DebugTimeManager::DebugTimeManager()
{
    qCDebug(logApp) << "DebugTimeManager initialized";

}

void DebugTimeManager::clear()
{
    qCDebug(logApp) << "Clearing all time points";
    m_MapPoint.clear();
    m_MapLinuxPoint.clear();
}

void DebugTimeManager::beginPointLinux(const QString &point, const QString &status)
{
    qCDebug(logApp) << QString("Starting time point: %1 (%2)").arg(point).arg(status);
    PointInfoLinux info;
    info.desc = status;
    timespec beginTime;
    int result = clock_gettime(CLOCK_MONOTONIC, &beginTime);
    if (result) {
        qCWarning(logApp) << "Failed to get monotonic clock time";
        return;
    }
    info.time = beginTime;
    m_MapLinuxPoint.insert(point, info);

}

void DebugTimeManager::endPointLinux(const QString &point, const QString &status)
{
    if (m_MapLinuxPoint.contains(point)) {
        timespec endTime;
        int result = clock_gettime(CLOCK_MONOTONIC, &endTime);
        if (result) {
            return;
        }
        timespec diffTime =  diff(m_MapLinuxPoint[point].time, endTime);
        qCInfo(logApp) << QString("[GRABPOINT] %1 %2 %3 time=%4s").arg(point).arg(m_MapLinuxPoint[point].desc).arg(status).arg(QString::number((diffTime.tv_sec * 1000 + (diffTime.tv_nsec) / 1000000) / 1000.0, 'g', 4));
        m_MapLinuxPoint.remove(point);
    }
}

timespec DebugTimeManager::diff(timespec start, timespec end)
{
    qCDebug(logApp) << QString("Calculating time difference: start=%1.%2 end=%3.%4")
        .arg(start.tv_sec).arg(start.tv_nsec)
        .arg(end.tv_sec).arg(end.tv_nsec);
    timespec temp;
    temp.tv_sec = end.tv_sec - start.tv_sec;
    temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    return temp;
}
