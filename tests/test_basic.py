import midas as md
import pandas as pd
from sklearn.metrics import roc_auc_score

# Load dataset
data = pd.read_csv("data/DARPA/darpa_processed.csv", names=['src', 'dst', 'timestamp'])
label = pd.read_csv("data/DARPA/darpa_ground_truth.csv", names=['label'])

def test_main():
    assert md.__version__ == "0.0.1"
    models = {
        'NormalCore': md.NormalCore(2, 769, 42),
        'RelationalCore': md.RelationalCore(2, 769, 42, 0.5),
        'FilteringCore': md.FilteringCore(2, 769, 42, 0.5, 0.5)
    }

    for name, model in models.items():
        score = []
        for x in data.values:
            score.append(model(x[0], x[1], x[2]))
        auc = roc_auc_score(label['label'], score)
        print(f'{name} auc: {auc}')

        assert auc > 0


if __name__ == '__main__':
    test_main()
