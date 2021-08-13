#ifndef __LABEL_H__
#define __LABEL_H__

#include "Node.h"

#include <string>
#include <map>

#include <QColor>
#include <QString>

class Label : public Node
{
public:
    static Label *create(const std::string &ttfFont);

public:
    Label(const std::string &font);
    virtual ~Label();
    virtual void draw(QPainter &painter, const Vec2 &vecDelta) override;

    void setString(const QString &str);
    void setFontSize(int size);
    void setSpacing(int spacing);
    void setColor(const QColor &color);

    static QString loadTTFFont(const QString &fileName);

private:
    int fontSize = 0;
    int spacing = 0;
    QString text;
    QString family;
    QColor color;
};

#endif
