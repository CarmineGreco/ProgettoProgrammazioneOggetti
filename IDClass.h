#ifndef IDCLASS_H
#define IDCLASS_H

class IDClass{

    protected:
        unsigned id;

    public:
        IDClass(){}
        IDClass(unsigned id){
            this->id = id;
        }

        unsigned getId() const { return id; }

};
#endif // IDCLASS_H
