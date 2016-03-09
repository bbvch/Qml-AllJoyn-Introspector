#pragma once

#include <QMetaType>
#include <memory>

#include "../ajintrospect/iobservablebussession.h"

Q_DECLARE_METATYPE(std::shared_ptr<IObservableBusSession>)
