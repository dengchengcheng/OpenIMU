#include "block.h"

Block::Block()
{

}
Block::Block(std::string blockType)
{
    this->blockType = blockType;
    inputSemaphore = 2;
}

Block::~Block()
{
    for(auto it = inputs.begin() ; it != inputs.end() ; it++)
        delete(*it);
    for(auto it = outputs.begin() ; it != outputs.end() ; it++)
        delete(*it);
}

void Block::SetStringID(const std::string value)
{
    stringID = value;
}

std::string Block::GetStringID()
{
    return stringID;
}


void Block::Notify(std::string inputID)
{
    inputSemaphore--;
    if(inputSemaphore == 0){
        work();
        inputSemaphore = 2;
    }
}

void Block::work()
{
    if(blockType == "mul")
    {
        // out = a + b
        std::cout<<"WORKING ON MUL!\n";

        int sum = GetInput("input1")->Get() * GetInput("input2")->Get();

        std::cout<<"mul result: "<<sum<<std::endl<<std::endl;

        GetOutput("output1")->Send(sum);
    }
    else if(blockType == "sub")
    {
        //out1 = a - b
        //out2 = b - a
        std::cout<<"WORKING ON SUB!\n\n";

        int res1 = GetInput("input1")->Get() - GetInput("input2")->Get();
        int res2 = GetInput("input2")->Get() - GetInput("input1")->Get();

        std::cout<<"sub result1: "<<res1<<std::endl;
        std::cout<<"sub result2: "<<res2<<std::endl<<std::endl;

        GetOutput("output1")->Send(res1);
        GetOutput("output2")->Send(res2);
    }
}

void Block::AddInput(InputNode* input)
{
    inputs.push_back(input);
    input->SetObserver(this);
}

void Block::AddOutput(OutputNode* output)
{
    outputs.push_back(output);
}

InputNode* Block::GetInput(std::string inputID)
{
    for ( std::vector<InputNode*>::iterator it = inputs.begin() ; it != inputs.end(); ++it)
    {
        if((*it)->GetStringID() == inputID) return *it;
    }
    return 0; //nullptr
}

OutputNode* Block::GetOutput(std::string outputID)
{
    for ( std::vector<OutputNode*>::iterator it = outputs.begin() ; it != outputs.end(); ++it)
    {
        if((*it)->GetStringID() == outputID) return *it;
    }
    return 0; //nullptr
}
