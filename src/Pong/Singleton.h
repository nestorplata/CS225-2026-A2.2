#pragma once

//Singleton template class
// taken from https://medium.com/@BobBrownConsulting/implementing-a-singleton-pattern-with-templates-3bc84c1090f6
//this is something I do, mostly for singletons, as polymrphism can be done simple using one class;
template <class _class_>
class Singleton
{
public:
    static _class_& instance()
    {
        if (instance_ == nullptr)
        {
            instance_ = std::unique_ptr<_class_>(new _class_);
        }

        return *instance_;
    }

private:
    static std::unique_ptr<_class_> instance_;
};
template <class _class_>
std::unique_ptr<_class_> Singleton<_class_>::instance_ = nullptr;