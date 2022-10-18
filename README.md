# MIDAS wrapped by pybind11

| CI                 | status                                                                |
| ------------------ | --------------------------------------------------------------------- |
| MSVC 2015          | [![AppVeyor][appveyor-badge]][appveyor-link]                          |
| conda.recipe       | [![Conda Actions Status][actions-conda-badge]][actions-conda-link]    |
| pip builds         | [![Pip Actions Status][actions-pip-badge]][actions-pip-link]          |
| [`cibuildwheel`][] | [![Wheels Actions Status][actions-wheels-badge]][actions-wheels-link] |

[gitter-badge]: https://badges.gitter.im/pybind/Lobby.svg
[gitter-link]: https://gitter.im/pybind/Lobby
[actions-badge]: https://github.com/pybind/cmake_example/workflows/Tests/badge.svg
[actions-conda-link]: https://github.com/pybind/cmake_example/actions?query=workflow%3A%22Conda
[actions-conda-badge]: https://github.com/pybind/cmake_example/workflows/Conda/badge.svg
[actions-pip-link]: https://github.com/pybind/cmake_example/actions?query=workflow%3A%22Pip
[actions-pip-badge]: https://github.com/pybind/cmake_example/workflows/Pip/badge.svg
[actions-wheels-link]: https://github.com/pybind/cmake_example/actions?query=workflow%3AWheels
[actions-wheels-badge]: https://github.com/pybind/cmake_example/workflows/Wheels/badge.svg
[appveyor-link]: https://ci.appveyor.com/project/dean0x7d/cmake-example/branch/master
[appveyor-badge]: https://ci.appveyor.com/api/projects/status/57nnxfm4subeug43/branch/master?svg=true

## Installation

```bash
pip install MIDAS
```

## Example

```python
import midas as md
# Load dataset
data = pd.read_csv("data/DARPA/darpa_processed.csv", names=['src', 'dst', 'timestamp'])
label = pd.read_csv("data/DARPA/darpa_ground_truth.csv", names=['label'])

models = {
    'midas': md.midas(2, 769, 42),
    'midasR': md.midasR(2, 769, 42, 0.5),
    'midasF': md.midasF(2, 769, 42, 0.5, 0.5)
}

for name, model in models.items():
    score = []
    for x in data.values:
        score.append(model(x[0], x[1], x[2]))
    auc = roc_auc_score(label['label'], score)
    print(f'{name} auc: {auc}')
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
git clone --recursive https://github.com/cliffxzx/midas.git
pip install ./midas
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
