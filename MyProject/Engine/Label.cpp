#include "Label.h"

#include <QByteArray>
#include <QFile>
#include <QFontDatabase>
#include <QString>

#include "Director.h"
using namespace std;

Label *Label::create(const string &ttfFont) {
    auto la = new (std::nothrow) Label{ttfFont};
    if (la) {
        la->autorelease();
        return la;
    }
    return nullptr;
}

Label::Label(const string &font) {
    text = "";
    color = QColor{255, 255, 255, 255};

    auto f = loadTTFFont(font.c_str());
    this->family = f;
}

Label::~Label() {}

void Label::draw(QPainter &painter, const Vec2 &vecDelta) {
    if (!isVisible()) return;
    auto pos = this->getPosition();
    auto scale = this->getScale();
    //监测scale
    if (scale.x <= 0) scale.x = 0.000001;  //不能为0
    if (scale.y <= 0) scale.y = 0.000001;  //不能为0
    pos = Director::instance->convertPosition(pos + vecDelta);

    QFont drawFont{"", this->fontSize, QFont::Normal, false};
    drawFont.setUnderline(false);
    drawFont.setOverline(false);
    drawFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    drawFont.setFamily(family);

    //渲染前准备
    painter.setOpacity(this->getOpacity());
    painter.translate(pos.x, pos.y);
    painter.scale(scale.x, scale.y);
    painter.rotate(this->getRotation());

    painter.setFont(drawFont);
    painter.setPen(this->color);

    //*****
    painter.drawText(0, 0, text);
    //*****

    //渲染后复原
    painter.rotate(-this->getRotation());
    painter.scale(1 / scale.x, 1 / scale.y);
    painter.translate(-pos.x, -pos.y);
    painter.setOpacity(1);
}

void Label::setString(const QString &str) { this->text = str; }

void Label::setFontSize(int size) { this->fontSize = size; }

void Label::setSpacing(int spacing) { this->spacing = spacing; }

void Label::setColor(const QColor &color) { this->color = color; }

QString Label::loadTTFFont(const QString &fileName) {
    static QHash<QString, QString> tmd;
    if (tmd.contains(fileName)) return tmd.value(fileName);
    QString font = "";
    QFile fontFile(fileName);
    if (!fontFile.open(QIODevice::ReadOnly)) return font;

    int loadedFontID =
        QFontDatabase::addApplicationFontFromData(fontFile.readAll());
    QStringList loadedFontFamilies =
        QFontDatabase::applicationFontFamilies(loadedFontID);
    if (!loadedFontFamilies.empty()) font = loadedFontFamilies.at(0);
    fontFile.close();

    if (!(font.isEmpty())) tmd.insert(fileName, font);
    return font;
}
