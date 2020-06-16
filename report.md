## 课程设计报告

2019 - 2020 学年春夏学期 《计算机图形学》

张海川 3180105353

章可循 3180104920

范安东 3180103126

### 实现功能

* 具有基本体素（立方体、球、圆柱、圆锥、多面棱柱、多面棱台）的建模表达能力
  * 曲面细分实现
* 具有基本 OBJ 三维网格导入导出功能
* 具有基本材质、纹理的显示和编辑能力
  * 可运行时调整材质、选择纹理
* 具有基本几何变换功能
  * 旋转、平移、缩放
* 基本光照明模型，具有基本的光源编辑能力
  * 可运行时调整光源的位置、开关
* 能对建模后场景进行漫游
  * 具有 Zoom In/Out, Pan, Orbit, Zoom To Fit 等观察功能
* 提供屏幕截取/保存功能
* 能够提供屏幕截取/保存功能
  * 根据数学原理手工实现

### 交互说明

blahblah 翻译一下readme好了

### 实现思路与代码分析

#### 总体框架设计

麻雀虽小，五脏俱全。我们的项目整体上基于一个场景图（scene graph）的架构进行实现，其中，世界中的每一个物体都是一个`node`对象，其核心代码如下：（省略了部分代码，具体请见[`scene_graph.h`](scene_graph.h)）

```c++
class node {
    protected:
            void transform();
            virtual void colorize();

    public:
        // transformation
        GLfloat translate[3]      = { 0.0f, 0.0f, 0.0f };
        GLfloat scale[3]          = { 1.0f, 1.0f, 1.0f };
        GLfloat center[3]         = { 0.0f, 0.0f, 0.0f };
        mat3    rotate_mat        = mat3::identity();

        // material
        std::shared_ptr<material> mtrl;

        // scene
        const std::string type    = "node";
        bool interactive          = true;
        bool visible              = true;

        virtual void update();
        virtual void render();
};
```

简单地说，每个`node`具有其位置、缩放和旋转（使用一个矩阵表示），它们决定了一个`node`的内部坐标系如何变换到世界坐标系；同时，每个`node`提供`update()`方法，负责更新其数据、以及`render()`方法，负责渲染对象本身。

这样做是为了解决图形学（尤其是在这样一个类似于游戏的需求中）里的一些常见问题：

1. 首先，`OpenGL`的API大量使用了状态机，其状态难以追踪，因此需要通过对其API进行封装，由框架维护`OpenGL`状态机的状态，并对外提供某种声明式的接口，从而降低各个模块之间的耦合程度，降低开发者的心智负担。在我们的框架中，矩阵变换以及材质设置分别通过`transform()`和`colorize()`函数进行封装，保证了其实现的正确性、防止对其他元素的渲染产生干扰，同时使得子类的实现变得十分简便。这样的封装也在其他许多地方有所体现，比如将材质抽象为[`material`类](material.h)等。
2. 其次，`OpenGL`作为一款相对底层的图形API，并不能处理所有的高级任务，比如我们项目中用到的“光线追踪”（从观察者的角度发出一束光线，找到这条线上遇到的第一个物体），就必须自己编写代码——而不是调用API——来实现。如果不使用框架、要求元素将位置写入`translate`等公有参数中，则会造成严重的代码耦合和数据冗余问题。这里，我们通过`node`类，定义了一个所有节点的**最小公共接口**，从而有效地解决了这些问题。
3. 除此之外，场景图所提供的抽象，也允许我们进行进一步的优化——比如在我们的项目中，要求每种节点提供其AABB（*Axis-Aligned Bounding Box*，坐标轴对齐包络盒），用于选中对象并显示选中框。实际上，这一抽象还能有更多价值，比如可以构建一棵八叉树（而不是简单地使用`vector`）、从而对视锥体外的对象进行消隐，大大加速场景渲染。当然，由于我们的项目尚未达到此等复杂程度，这样的优化只会成为overkill而已。
4. 最后，场景图提供了一套行之有效的生命周期管理，比如每个`node`应当在其构造函数中进行初始化（此时`glut`已经完成`OpenGL`上下文的初始化），然后在`update()`中进行逻辑更新（此时不保证`OpenGL`状态机的状态），最后在`render()`中进行绘制（此时所有的`update()`均已执行完毕，并且保证对象坐标系变换到视坐标系等）。这也有助于各个模块的实现者做出合理、可靠、高效的实现，减少可能出现的问题。

综上，我们的项目建立在一系列抽象上——节点`node`、场景图`scene_graph`、光源`light`、控制器`control`、摄像机`camera`……它们是其他一切的基础，是各种复杂功能背后那坚实的后盾。

#### 场景漫游

zhc

#### 体素构建

fad

#### 曲面细分

zhc

#### OBJ 网格导入与导出

fad

#### 材质与纹理显示与编辑

fad

#### 几何变换

zkx

####  光照模型

zkx

#### 屏幕截取

zkx

#### Nurbs 建模

zkx

### 分工

张海川：`scene_graph` 维护、glut 生命周期管理、项目框架设计与协调、曲面细分、运动控制

范安东：场景编辑、体素建模、纹理控制、OBJ 文件导入导出、展示视频剪辑

章可循：场景编辑、变换控制、光源控制、截图、Nurbs 建模、展示视频录制与配音
