#pragma once

#include <memory>
#include <vector>

#include "alljoyn/MsgArg.h"
#include "alljoyn/Message.h"

#include "argumentlist.h"


class AjArgumentList : public ArgumentList
{
public:
    AjArgumentList();
    ~AjArgumentList() = default;

    std::string signature() const override;
    void addString(std::string value) override;
    std::string getString(size_t index) const override;

    size_t size() const;
    const ajn::MsgArg* data() const;
    static std::unique_ptr<AjArgumentList> fromMessage(ajn::Message& msg);

private:
    std::vector<ajn::MsgArg> args;
    std::string signature_str;
};
