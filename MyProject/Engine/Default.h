#ifndef __DEFAULT_H__
#define __DEFAULT_H__

#define DISABLE_AUDIO 1

//更新的延迟毫秒数
namespace Def {
constexpr float updateDelay = 1.0f / 65;
}

#include <QByteArray>
#include <QString>
#include <string>

inline QString str2qstr(const std::string& str) {
    return QString::fromLocal8Bit(str.data());
}

inline std::string qstr2str(const QString& qstr) {
    QByteArray cdata = qstr.toLocal8Bit();
    return std::string(cdata);
}

#endif
