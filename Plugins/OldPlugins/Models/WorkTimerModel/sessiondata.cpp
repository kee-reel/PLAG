#include "sessiondata.h"

SessionData::SessionData()
{
}

QString SessionData::getSessionType() const
{
    switch (sessionType)
    {
        case SessionData::Work:
            return "Work";
            break;

        case SessionData::Lesure:
            return "Lesure";
            break;
    }
}

void SessionData::setSessionType(const QString &value)
{
    if(value == "Work")
    {
        sessionType = Work;
        return;
    }

    if(value == "Lesure")
    {
        sessionType = Lesure;
        return;
    }
}
