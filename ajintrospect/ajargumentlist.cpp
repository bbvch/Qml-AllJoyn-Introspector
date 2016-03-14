#include <stdexcept>

#include "ajargumentlist.h"


AjArgumentList::AjArgumentList()
{

}

AjArgumentList::AjArgumentList();

std::string AjArgumentList::signature() const
{
    return signature_str;
}

void AjArgumentList::addString(std::string value)
{
    signature_str += "s";
    args.emplace_back("s", value.c_str());
    args.back().Stabilize();
}

std::string AjArgumentList::getString(size_t index) const
{
    auto& arg = args.at(index);
    if(arg.HasSignature("s"))
    {
        return arg.v_string.str;
    }
    else
    {
        throw std::invalid_argument{"Argument is not of type string"};
    }
}

std::unique_ptr<AjArgumentList> AjArgumentList::fromMessage(ajn::Message& msg)
{
    auto list = std::make_unique<AjArgumentList>();

    size_t n_args = 0;
    const ajn::MsgArg *args;
    msg->GetArgs(n_args, args);

    for(size_t i=0; i<n_args; ++i)
    {
        auto& arg = args[i];

        if(arg.HasSignature("s"))
        {
            list->addString(arg.v_string.str);
        }
        else if(arg.HasSignature("as"))
        {
            const char ** vals;
            size_t n_vals = 0;
            arg.Get("as", &n_vals, &vals);

            for(size_t j=0; j<n_vals; ++j)
            {
                list->addString(vals[j]);
            }
        }
    }
    return list;
}

size_t AjArgumentList::size() const
{
    return args.size();
}

const ajn::MsgArg* AjArgumentList::data() const
{
    return args.data();
}
