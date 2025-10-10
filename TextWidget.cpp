#include "TextWidget.h"

#include <memory>

#include "ConsoleRender.h"

TextWidget::TextWidget(std::shared_ptr<ConsoleRender> render, int xStart, int xEnd, int y) : xStart(xStart), xEnd(xEnd), y(y), render(render) {}

void TextWidget::setText(std::u32string _text) {
    text = std::move(_text);
    for (int i = xStart; i <= xEnd; i++) {
        render->setChar(i, y, U'\0');
    }
    for (int i = 0; i < text.size(); i++) {
        render->setChar(i + xStart, y, text[i]);
    }
    render->reRender();
}

void TextWidget::setText(std::string _text) {
    std::u32string txt(_text.begin(), _text.end());
    setText(std::move(txt));
}

void TextWidget::appendText(std::string _text) {
    std::u32string txt(_text.begin(), _text.end());
    setText(text + txt);
}
std::u32string_view TextWidget::getText() const {
    return text;
}
