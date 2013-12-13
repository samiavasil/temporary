#ifndef GENERATOR_H
#define GENERATOR_H
#include<QString>
class output_writer;
class data_manager;

class generator
{
public:
    generator();

    int generateNodeData( data_manager *mng, QString &NodeName, output_writer *writer );
};

#endif // GENERATOR_H
