# 3DViewerCpp
Implementation project 3DViewer on c++

В данном проекте реализовано приложение для просмотра 3D моделей в формате .obj файлов в каркасном виде на языке программирования С++.
Графическая часть реализована на QT. Применены патерны проектирования MVC, SingleTon.

### Technologies used:
* [Qt](https://www.qt.io/), [OpenGL](https://www.opengl.org/)
* [MVC](https://m.wikipedia.org/wiki/Model–view–controller), [Singleton](https://m.wikipedia.org/wiki/Singleton_pattern)

## Features

- Загрузка моделей в obj формате.

- Интерфейс позволяющий двигать, поворачивать и масштабировать модель, а также косметические опреации (изменение цвета и др).

- Сохранение изображения модели в виде картинки (bmp/jpeg), либо в формате gif.

- Сохранение и загрузка настроек отображения модели.

## Installation

1. Для cборки проекта, находясь в директории 3DViewerCpp, прописать:
```sh
make
```
2. Запустить проект:
```sh
make open
```

  
