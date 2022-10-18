# flow-midas: MIDAS wrapped by pybind11

|   CI   |                  MSVC 2015                   |                            conda.recipe                            |                          pip builds                          |                          [`cibuildwheel`][]                           |
| :----: | :------------------------------------------: | :----------------------------------------------------------------: | :----------------------------------------------------------: | :-------------------------------------------------------------------: |
| Status | [![AppVeyor][appveyor-badge]][appveyor-link] | [![Conda Actions Status][actions-conda-badge]][actions-conda-link] | [![Pip Actions Status][actions-pip-badge]][actions-pip-link] | [![Wheels Actions Status][actions-wheels-badge]][actions-wheels-link] |

[actions-badge]: https://github.com/cliffxzx/midas/workflows/Tests/badge.svg
[actions-conda-link]: https://github.com/cliffxzx/midas/actions?query=workflow%3A%22Conda
[actions-conda-badge]: https://github.com/cliffxzx/midas/workflows/Conda/badge.svg
[actions-pip-link]: https://github.com/cliffxzx/midas/actions?query=workflow%3A%22Pip
[actions-pip-badge]: https://github.com/cliffxzx/midas/workflows/Pip/badge.svg
[actions-wheels-link]: https://github.com/cliffxzx/midas/actions?query=workflow%3AWheels
[actions-wheels-badge]: https://github.com/cliffxzx/midas/workflows/Wheels/badge.svg
[appveyor-link]: https://ci.appveyor.com/project/cliffxzx/midas/branch/master
[appveyor-badge]: https://ci.appveyor.com/api/projects/status/bnirfs3lq8aa7dls?svg=true

This python package is a wrapper of [this c++ source](https://github.com/Stream-AD/MIDAS) code. Thanks to the author!

## Installation

```bash
pip install flow-midas
```

## Example

```python
import midas as md

# Load dataset
data = pd.read_csv("data/DARPA/darpa_processed.csv", names=['src', 'dst', 'timestamp'])
label = pd.read_csv("data/DARPA/darpa_ground_truth.csv", names=['label'])

models = {
    "NormalCore": md.NormalCore(2, 769, 42),
    "RelationalCore": md.RelationalCore(2, 769, 42, 0.5),
    "FilteringCore": md.FilteringCore(2, 769, 42, 0.5, 0.5),
}

for name, model in models.items():
    score = []
    for x in data.values:
        score.append(model(x[0], x[1], x[2]))
    auc = roc_auc_score(label["label"], score)
    print(f"{name} auc: {auc}")

    assert auc > 0
```

## Development

### Prerequisites

- A compiler with C++11 support
- Pip 10+ or CMake >= 3.4 (or 3.8+ on Windows, which was the first version to support VS 2015)
- Ninja or Pip 10+

### Installation

Just clone this repository and pip install. Note the `--recursive` option which is
needed for the pybind11 submodule:

```bash
git clone --recursive https://github.com/cliffxzx/flow-midas.git
pip install ./flow-midas

```

With the `setup.py` file included in this example, the `pip install` command will
invoke CMake and build the pybind11 module as specified in `CMakeLists.txt`.

### Building the documentation

Documentation for the example project is generated using Sphinx. Sphinx has the
ability to automatically inspect the signatures and documentation strings in
the extension module to generate beautiful documentation in a variety formats.
The following command generates HTML-based reference documentation; for other
formats please refer to the Sphinx manual:

- `cd midas/docs`
- `make html`

[`cibuildwheel`]: https://cibuildwheel.readthedocs.io

## Citation

If you use this code for your research, please consider citing the arXiv preprint

```bibtex
@misc{bhatia2020realtime,
    title={Real-Time Anomaly Detection in Edge Streams},
    author={Siddharth Bhatia and Rui Liu and Bryan Hooi and Minji Yoon and Kijung Shin and Christos Faloutsos},
    booktitle={Transactions on Knowledge Discovery from Data (TKDD)},
    year={2022}
}

```

or the AAAI paper

```bibtex
@inproceedings{bhatia2020midas,
    title="MIDAS: Microcluster-Based Detector of Anomalies in Edge Streams",
    author="Siddharth {Bhatia} and Bryan {Hooi} and Minji {Yoon} and Kijung {Shin} and Christos {Faloutsos}",
    booktitle="AAAI Conference on Artificial Intelligence (AAAI)",
    year="2020"
}
```
