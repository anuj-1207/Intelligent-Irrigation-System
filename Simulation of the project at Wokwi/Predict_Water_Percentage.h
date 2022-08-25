// #include<iostream>
#ifndef Start

// #include<iostream>
#include <math.h>
// using namespace std;

const int m = 8;
float hidden_layer_input[8];
float hidden_layer_output[9];
float output = 0;

//multiply hidden layer with weights
void input_multliply(float input[],int size,float weights[][m],int column){
    
    int rows = size;
    int cols = column;
    float temp[rows][cols];
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            temp[i][j] = input[i]*weights[i][j];
        }
    }
    
    
    for (int i = 0; i < cols; i++)
    { 
        hidden_layer_input[i]=0;
    }
    
    for (int i = 0; i < cols; i++)
    {
        float sum = 0;
        for (int j = 0; j < rows; j++)
        {
           sum = sum + temp[j][i];
        }
        hidden_layer_input[i] = sum;
    }
    
   
}


//multiply last hidden layer with weights
void input_multliply_last(float input[],int size,float weights[][1],int column){
    
    int rows = size;
    int cols = column;
    float temp[rows][cols];
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            temp[i][j] = input[i]*weights[i][j];
        }
    }
    
             
    for (int i = 0; i < 9; i++)
    { 
        hidden_layer_input[i]=0;
    }
    
    for (int i = 0; i < cols; i++)
    {
        float sum = 0;
        for (int j = 0; j < rows; j++)
        {
           sum = sum + temp[j][i];
        }
        hidden_layer_input[i] = sum;
    }
    
           
    //         for (int i = 0; i < 9; i++)
    // {
    //     cout << "Element at x[" << i
    //              << "]: ";
    //         cout << hidden_layer_input[i]<<endl;
    // }   
   
}


//relu function
void relu(float input[],int size){
     
    for (int i = 0; i < size; i++)
    {
         if(input[i] <= 0){
             hidden_layer_output[i] = 0;
         }
         else{
             hidden_layer_output[i] = input[i];
         }
    }
    hidden_layer_output[8] = 1;
    
}


//sigmoid function
void sigmoid (float input[]) {
    
        output = 1 / (1 + exp(-input[0]));

}
float hi(float temp,float humid)
{
    float sum = temp + humid ;
    float average = sum / 1.8;
    average = average / 100;
    return average;
}



float predict_water_percentage(float humid,float temp)
{
    
    float input_layer_weights[3][8]={{-0.57856506, -0.08213568, -0.43907085, -0.3036409 ,  0.6628046 ,
         0.7553534 ,  0.14372635, -0.58095}, 
        {0.7047597 ,  0.23441976,  0.67971057,  0.33483654,  0.44590095,
        -0.0584395 , -0.13762644,  0.3444005},
         { 1.4179127 ,  1.4513916 , -1.4929569 , -1.6073055 ,  1.390608  ,
       -1.4216737 ,  0.05530057, -0.9563677 } };
    
    float hidden_layer1_weights[9][8] = {{1.5516937e-01,  5.6129348e-01,  2.2516549e-02,  2.4412899e-01,
         3.6624610e-02, -4.5448765e-01, -6.0169131e-01, -5.1730037e-01},
       { -2.1695161e-01,  2.8361738e-02,  4.6541947e-01, -3.5534343e-01,
        -2.4739426e-01, -4.6642619e-01,  4.3568903e-01, -2.5766808e-01 },
       { 3.3468533e-01, -6.4768195e-01, -3.8006696e-01,  4.6726620e-01,
         1.5526694e-01,  6.2384880e-01,  7.2748661e-02, -4.0549198e-01},
       {-5.1918674e-01,  1.8421386e-01,  4.2709357e-01, -2.8380901e-02,
        -4.5937833e-01,  5.7226741e-01,  7.0705950e-02, -6.1351919e-01 },
       { -1.3994747e-01,  2.2426999e-01, -4.9765688e-01, -2.3706533e-01,
        -5.0361603e-01,  3.6819230e-04, -3.0711055e-01,  2.7115712e-01},
       { -2.5531554e-01, -1.4276426e-01, -1.7011669e-01,  1.5578221e-01,
         4.2961198e-01,  3.9575061e-01, -4.4658571e-01,  4.7308582e-01},
       {3.4947640e-01,  3.8480696e-01,  2.8866029e-01,  5.3804487e-01,
        -3.5651919e-01,  1.6140446e-01,  1.2305534e-01, -2.0509973e-02 },
       { -3.4879676e-01, -1.4858256e-01, -3.3995202e-01, -2.8799796e-01,
        -2.2261965e-01,  6.1543542e-01,  4.3480152e-01, -4.1647887e-01 },
       {0.        ,  1.4347509 ,  0.        ,  1.3279197 ,  0.        ,
       -1.478049  ,  0.        ,  0.58443433}};
    
    float hidden_layer2_weights[9][1] = {{-0.03359169 }, { -0.48137376}, { -0.7854406}, {-0.08404907},
       {-0.37638563}, {0.41627768}, {-0.02935261},{-3.1762486  },{-1.4324794}};
       
       
    float input_layer[3] = {humid,temp,1};  //humid,temp,bias   
       
    input_multliply(input_layer,3,input_layer_weights,8);   
    relu(hidden_layer_input,8);
    input_multliply(hidden_layer_output,9,hidden_layer1_weights,8);
    relu(hidden_layer_input,8);
    input_multliply_last(hidden_layer_output,9,hidden_layer2_weights,1);
    sigmoid(hidden_layer_input);
    
    //cout<<output;
    return output;
}
#endif
