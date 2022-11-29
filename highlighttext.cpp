#include "highlighttext.h"

Highlighttext::Highlighttext(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;
    //c++关键词的设置
    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    const QString keywordPatterns[] = {
        QStringLiteral("\\bchar\\b"),       QStringLiteral("\\bclass\\b"),      QStringLiteral("\\bconst\\b"),
        QStringLiteral("\\bdouble\\b"),     QStringLiteral("\\benum\\b"),       QStringLiteral("\\bexplicit\\b"),
        QStringLiteral("\\bfriend\\b"),     QStringLiteral("\\binline\\b"),     QStringLiteral("\\bint\\b"),
        QStringLiteral("\\blong\\b"),       QStringLiteral("\\bnamespace\\b"),  QStringLiteral("\\boperator\\b"),
        QStringLiteral("\\bprivate\\b"),    QStringLiteral("\\bprotected\\b"),  QStringLiteral("\\bpublic\\b"),
        QStringLiteral("\\bshort\\b"),      QStringLiteral("\\bsignals\\b"),    QStringLiteral("\\bsigned\\b"),
        QStringLiteral("\\bslots\\b"),      QStringLiteral("\\bstatic\\b"),     QStringLiteral("\\bstruct\\b"),
        QStringLiteral("\\btemplate\\b"),   QStringLiteral("\\btypedef\\b"),    QStringLiteral("\\btypename\\b"),
        QStringLiteral("\\bunion\\b"),      QStringLiteral("\\bunsigned\\b"),   QStringLiteral("\\bvirtual\\b"),
        QStringLiteral("\\bvoid\\b"),       QStringLiteral("\\bvolatile\\b"),   QStringLiteral("\\bbool\\b"),
        QStringLiteral("\\b#include\\b"),   QStringLiteral("\\b#return\\b")
    };

    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.push_back(rule);
    }

    /* 定义引号高亮规则：模式具有正则表达式的形式 例如： "......"
     * 并以相关格式存储在HighlightingRule对象中。 */
    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression(QStringLiteral("\".*\""));
    rule.format = quotationFormat;
    highlightingRules.push_back(rule);

    /* 定义函数的高亮规则：模式具有正则表达式的形式，例如：My_func(
     * 并以相关格式存储在HighlightingRule对象中。
     * regex 只检测了左括号的存在，即认为是函数名*/
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegularExpression(QStringLiteral("\\b[A-Za-z0-9_]+(?=\\()"));
    rule.format = functionFormat;
    highlightingRules.push_back(rule);

    // 单行注释的高亮（//）
    singleLineCommentFormat.setForeground(Qt::red);
    rule.pattern = QRegularExpression(QStringLiteral("//[^\n]*"));
    rule.format = singleLineCommentFormat;
    highlightingRules.push_back(rule);
}

void Highlighttext::highlightBlock(const QString &document)
{
    for(int i=0;i<highlightingRules.size();i++)
    {
        QRegularExpressionMatchIterator matchIterator =
              highlightingRules[i].pattern.globalMatch(document);
               while (matchIterator.hasNext()) {
                   QRegularExpressionMatch match = matchIterator.next();
                   setFormat(match.capturedStart(),
                   match.capturedLength(), highlightingRules[i].format);
               }
    }
}
