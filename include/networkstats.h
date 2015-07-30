#ifndef NETWORKSTATS_H
#define NETWORKSTATS_H


class networkstats
{
    public:
        networkstats();
        virtual ~networkstats();
        void setdeviceNum(char*);
    private:
        int devicenumer;

};
#endif // NETWORKSTATS_H
