#pragma once

#include <vector>
#include <string>

class ArgumentList
{
public:
    virtual ~ArgumentList() = default;
    virtual std::string signature() const = 0;
    virtual size_t size() const = 0;
    virtual void addString(std::string value) = 0;
    virtual std::string getString(size_t index) const = 0;
};
