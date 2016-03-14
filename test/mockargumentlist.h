#pragma once

#include <string>

#include <QList>
#include <QVariant>

#include "../ajintrospect/argumentlist.h"


class MockArgumentList : public ArgumentList
{
public:
    std::string signature() const override
    {
        return "";
    }

    size_t size() const override
    {
        return args.length();
    }

    void addString(std::string s) override
    {
        args.push_back(QString::fromStdString(s));
    }

    std::string getString(size_t i) const override
    {
        return args.at(i).toString().toStdString();
    }

    QList<QVariant> args;
};
