import pandas as pd
from sklearn.datasets import load_breast_cancer
import pickle

# Load breast cancer dataset
cancer_data = load_breast_cancer()
df = pd.DataFrame(data=cancer_data.data, columns=cancer_data.feature_names)
df['target'] = cancer_data.target

# Save DataFrame to a pickle file
with open('breast_cancer_data.pkl', 'wb') as file:
    pickle.dump(df, file)

print("Pickle file created successfully.")