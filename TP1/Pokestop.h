class Pokestop {
public:
    Pokestop();
    virtual ~Pokestop();
    
    virtual void visiter();

private:
    virtual bool _estActif();

private:
    int _distAvantActif;
};