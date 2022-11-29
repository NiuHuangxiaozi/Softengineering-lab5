#ifndef HIGHLIGHTTEXT_H
#define HIGHLIGHTTEXT_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include<vector>
#include <QSyntaxHighlighter>
#include <QRegularExpressionMatchIterator>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include <QTextCharFormat>
#include <QTextDocument>
class Highlighttext: public QSyntaxHighlighter
{
    Q_OBJECT
public:
    Highlighttext(QTextDocument *parent =nullptr);
    void highlightBlock(const QString &document);
    struct HighlightingRule
    {
         QRegularExpression pattern;
         QTextCharFormat format;
    };
    std::vector<HighlightingRule> highlightingRules;
    //以下是各种正则匹配
    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
};

#endif // HIGHLIGHTTEXT_H
