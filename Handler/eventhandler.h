
#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

#include<vector>
#include <algorithm>
#include<memory>

template <typename T>
class EventHandler{
    public:
        class Listener{
           public:
                virtual ~Listener(){ };
                virtual void Update(T *, EventHandler& Sender) {};
            } ;
    private:
            typedef std::shared_ptr<Listener> ListenerPtr;
            typedef std::vector<ListenerPtr> Listeners;
            Listeners ListenersList;

    public:
           virtual void Attach(ListenerPtr listener){
                if(ListenersList.end() != std::find(ListenersList.begin(), ListenersList.end(), listener))
                    return;
                ListenersList.push_back(listener);
            }

           virtual void Dettach(ListenerPtr listener){
                ListenersList.erase(std::remove(ListenersList.begin(), ListenersList.end(), listener), ListenersList.end());
            }

           virtual void Notify(ListenerPtr Target, T * Event){
                for(typename Listeners::const_iterator it = ListenersList.begin(); it != ListenersList.end(); ++it)
                    if(*it == Target)
                        (*it)->Update(Event, *this);
            }
};

#endif
