# Model Training

## Usage
1. Push all the files that you edited to GitHub.
2. If your repo on GitHub is public,  
   you can run the jupyter notebook in `https://colab.research.google.com/github/<your_username>/<your_repo_name>/blob/master/src/model_train/train_magic_wand_model.ipynb`  
   where `<your_username>` may be NTHUEE240500 and `<your_repo_name>` may be mbed07.  
   Otherwise, you may check [Loading Private Notebooks section in Using Google Colab with GitHub](https://colab.research.google.com/github/googlecolab/colabtools/blob/master/notebooks/colab-github-demo.ipynb).
3. Replace the `you_repo_url` and `your_repo_name` in the Google colab to satify the situation you have.
4. Press the play button beside the cell to run the code in the cell.

<br>

Note: You can tune some parameters in the `config.py`
```python
DATA_NAME = "accel_ms2_xyz"
LABEL_NAME = "gesture"

# label name (you should keep "negative" in the end of the list)
labels = ["ring", "slope", "negative"]

# data split configuration
# note that train_ratio + valid_ratio + test_ratio = 1
train_ratio = 0.6
valid_ratio = 0.3
data_split_random_seed = 30

# model configuration
model = "CNN"
seq_length = 64 # the input size of the model
epochs = 50
steps_per_epoch =1000
batch_size = 64
```

