# Data Deployment

## Getting Started

1. mbed OS Version: 5.14.0
2. TensorFlow Lite Version: 2.1.0

## Usage

1. `$ sudo mbed compile -m K66F -t GCC_ARM --profile tflite.json -f`
2. `$ sudo screen /dev/<devicename>`

<br>

Note: You can change the config in `config.h`

## TensorFlow Lite Functions Used in this Project

### Logging method
```cpp
static tflite::MicroErrorReporter micro_error_reporter;
tflite::ErrorReporter* error_reporter = &micro_error_reporter;
error_reporter->Report("Message\n");
The implement method is similar to the code below but it will preprocess the variable you give it before printed.

void DebugLog(const char* s) {
  static Serial pc(USBTX, USBRX);
  pc.printf("%s", s);
}
```

### Load a model

Load a model from char array.

```cpp
const tflite::Model* model = tflite::GetModel(g_magic_wand_model_data);
```

### Operations resolver

This will be used by the interpreter to access the operations.

To figure out the operations that provided by TensorFlow Lite, please check https://github.com/tensorflow/tensorflow/blob/master/tensorflow/lite/micro/kernels/all_ops_resolver.cc

```cpp
tflite::ops::micro::AllOpsResolver micro_op_resolver;
```

#### Just load the operation implementations we need

The AllOpsResolver loads all of the operations available in TensorFlow Lite for Microcontrollers, which uses a lot of memory. Since a given model will only use a subset of these operations, it's recommended that real world applications load only the operations that are needed.

To load the operation implementations we need, use the method below instead.
```cpp
static tflite::MicroOpResolver<op_num> micro_op_resolver;
micro_op_resolver.AddBuiltin(tflite::BuiltinOperator_OP_NAME, tflite::ops::micro::Register_OP_NAME());
```

### Interpreter

#### Allocate memory

We need to preallocate some of memory for input, output, and intermediate arrays.

```cpp
const int tensor_arena_size = 60 * 1024;
uint8_t tensor_arena[tensor_arena_size];
```

#### Build the interpreter
```cpp
static tflite::MicroInterpreter static_interpreter(model, micro_op_resolver, tensor_arena, kTensorArenaSize, error_reporter);
tflite::MicroInterpreter* interpreter = &static_interpreter;
```

#### Allocate tensors
```cpp
interpreter->AllocateTensors();
```

#### Get the pointer to model input
```cpp
TfLiteTensor* model_input = interpreter->input(0);
```

#### Validate input shape

You can modify the condition to match your model.

```cpp
if ((model_input->dims->size != 4) || (model_input->dims->data[0] != 1) ||
    (model_input->dims->data[1] != config.seq_length) ||
    (model_input->dims->data[2] != kChannelNumber) ||
    (model_input->type != kTfLiteFloat32)) {
    error_reporter->Report("Bad input tensor parameters in model");
    return -1;
}
```

#### Provide an input value
```cpp
model_input->data.f[0] = 0.;
```

In this project, we use a function to provide an input value.
```cpp
got_data = ReadAccelerometer(error_reporter, model_input->data.f, input_length, should_clear_buffer);
```

#### Run the model
```cpp
TfLiteStatus invoke_status = interpreter->Invoke();
if (invoke_status != kTfLiteOk) {
  error_reporter->Report("Invoke failed\n");
}
```

### Obtain the output
```cpp
TfLiteTensor* output = interpreter->output(0);
float value = output->data.f[0];
```

In this project, we use a function to obtain the output value.
```cpp
gesture_index = PredictGesture(interpreter->output(0)->data.f);
```

