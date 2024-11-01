#ifndef VISITOR
#define VISITOR

class IVisitor
{
public:
    virtual void visit(class DoubleDamageSettings* settings) = 0;

    virtual void visit(class ScannerSettings* settings) = 0;

    virtual void visit(class BombardmentSettings* settings) = 0;
};

#endif