#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <wayland-client.h>
#include <wayland-server.h>
#include <wayland-client-protocol.h>
#include <wayland-egl.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
//#include <GL/gl.h>
#include <cassert>
#include <sys/time.h>

using namespace std;

struct GLColor
{
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;

    GLColor()
        : r(0.0f)
        , g(0.0f)
        , b(0.0f)
        , a(1.0f)
    {}
    GLColor(GLfloat r, GLfloat g, GLfloat b)
        : r(r)
        , g(g)
        , b(b)
        , a(1.0f)
    {}
    GLColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {}
};

class WaylandServer
{
public:
    WaylandServer()
        : _display(nullptr)
    {}
    bool Initialize()
    {
        _display = wl_display_connect(nullptr);
        if (_display == nullptr)
        {
            cerr << "Can't connect to display" << endl;
            return false;
        }
        cout << "connected to display" << endl;

        wl_registry * registry = wl_display_get_registry(_display);
        wl_registry_add_listener(registry, &_registryListener, nullptr);

        wl_display_dispatch(_display);
        wl_display_roundtrip(_display);

        if (_compositor == nullptr || _shell == nullptr)
        {
            cerr << "Can't find compositor or shell" << endl;
            return false;
        } else
        {
            cerr << "Found compositor and shell" << endl;
        }
        return true;
    }

    const wl_display * Display() const { return _display; }
    const wl_compositor * Compositor() const { return _compositor; }
    const wl_shell * Shell() const { return _shell; }

private:
    wl_display * _display;
    static wl_compositor * _compositor;
    static wl_shell * _shell;
    static const wl_registry_listener _registryListener;

    static void GlobalRegistryHandler(void * data, struct wl_registry * registry,
                                      uint32_t id, const char * interface, uint32_t version)
    {
        cout << "Got a registry event for " << interface << " id " << id << endl;
        if (!strcmp(interface, "wl_compositor"))
        {
            _compositor = reinterpret_cast<wl_compositor *>(wl_registry_bind(registry, id, &wl_compositor_interface, 1));
        } else if (!strcmp(interface, "wl_shell"))
        {
            _shell = reinterpret_cast<wl_shell *>(wl_registry_bind(registry, id, &wl_shell_interface, 1));
        }
    }

    static void GlobalRegistryRemover(void *data, struct wl_registry *registry, uint32_t id)
    {
        cout << "Got a registry losing event for " << id << endl;
    }
};

wl_compositor * WaylandServer::_compositor = nullptr;
wl_shell * WaylandServer::_shell = nullptr;

const wl_registry_listener WaylandServer::_registryListener =
{
    WaylandServer::GlobalRegistryHandler,
    WaylandServer::GlobalRegistryRemover
};

class EGLWindow
{
public:
    EGLWindow()
        : _majorVersion(0)
        , _minorVersion(0)
        , _eglWindow(nullptr)
    {}
    virtual ~EGLWindow()
    {
    }
    
    bool Initialize(const wl_display * display)
    {
        if (!SetupDisplay(display))
            return false;
        if (!InitializeEGL())
            return false;
        if (!DetermineConfiguration())
            return false;
        SetupContext();
        return true;
    }
    bool Shutdown()
    {
        return TerminateEGL();
    }

    bool CreateWindow(const wl_surface * surface, int _width, int _height)
    {
        _eglWindow = wl_egl_window_create(const_cast<wl_surface *>(surface), _width, _height);
        if (_eglWindow == EGL_NO_SURFACE)
        {
            cerr << "Can't create egl window" << endl;
            return false;
        } else
        {
            cerr << "Created egl window" << endl;
        }

        _eglSurface = eglCreateWindowSurface(_eglDisplay, _eglConf, _eglWindow, nullptr);

        if (eglMakeCurrent(_eglDisplay, _eglSurface, _eglSurface, _eglContext))
        {
            cerr << "Made current" << endl;
        } else
        {
            cerr << "Make current failed" << endl;
        }
        return true;
    }
    void SwapBuffers()
    {
        if (eglSwapBuffers(_eglDisplay, _eglSurface))
        {
//            cerr << "Swapped buffers" << endl;
        } else
        {
            cerr << "Swapped buffers failed" << endl;
        }
    }

private:
    EGLint _majorVersion;
    EGLint _minorVersion;
    wl_egl_window * _eglWindow;
    EGLSurface _eglSurface;
    EGLDisplay _eglDisplay;
    EGLContext _eglContext;
    EGLConfig _eglConf;

    bool SetupDisplay(const wl_display * display)
    {
        _eglDisplay = eglGetDisplay((EGLNativeDisplayType) display);
        if (_eglDisplay == EGL_NO_DISPLAY)
        {
            cerr << "Can't create EGL display" << endl;
            return false;
        } else
        {
            cerr << "Created EGL display" << endl;
        }
        return true;
    }
    bool InitializeEGL()
    {
        if (eglInitialize(_eglDisplay, &_majorVersion, &_minorVersion) != EGL_TRUE)
        {
            cerr << "Can't initialize EGL display" << endl;
            return false;
        }
        cout << "EGL version: " << _majorVersion << "." << _minorVersion << endl;
        return true;
    }
    bool TerminateEGL()
    {
        if (eglTerminate(_eglDisplay) != EGL_TRUE)
        {
            cerr << "Can't terminate EGL display" << endl;
            return false;
        }
        return true;
    }
    bool DetermineConfiguration()
    {
        EGLConfig * configs;
        EGLint count;
        EGLint n, size;
        int i;
        EGLint configAttribs[] =
            {
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_RED_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_BLUE_SIZE, 8,
                EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                EGL_NONE
            };
        
        
        eglGetConfigs(_eglDisplay, nullptr, 0, &count);
        cout << "EGL has " << count << " configs" << endl;

        configs = new EGLConfig[count];

        eglChooseConfig(_eglDisplay, configAttribs, configs, count, &n);

        cout << "EGL has " << n << " matching configs" << endl;

        for (i = 0; i < n; i++)
        {
            eglGetConfigAttrib(_eglDisplay,
                               configs[i], EGL_BUFFER_SIZE, &size);
            cout << "Buffer size for config " << i << " is " << size << endl;
            eglGetConfigAttrib(_eglDisplay,
                               configs[i], EGL_RED_SIZE, &size);
            cout << "Red size for config " << i << " is " << size << endl;

            // just choose the first one
            _eglConf = configs[i];
            break;
        }
        delete [] configs;
        return true;
    }
    void SetupContext()
    {
        static const EGLint contextAttribs[] =
        {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE
        };
        _eglContext = eglCreateContext(_eglDisplay, _eglConf, EGL_NO_CONTEXT, contextAttribs);
    }
};

static const char *vert_shader_text =
    "uniform mat4 rotation;\n"
        "attribute vec4 pos;\n"
        "attribute vec4 color;\n"
        "varying vec4 v_color;\n"
        "void main() {\n"
        "  gl_Position = rotation * pos;\n"
        "  v_color = color;\n"
        "}\n";

static const char *frag_shader_text =
    "precision mediump float;\n"
        "varying vec4 v_color;\n"
        "void main() {\n"
        "  gl_FragColor = v_color;\n"
        "}\n";

static const char * texture_vertex_shader =
    "#version 300 es\n"
    "\n"
    "precision mediump float;\n"
    "// Input vertex data, different for all executions of this shader.\n"
    "layout(location = 0) in vec3 vertexPosition_modelspace;\n"
    "layout(location = 1) in vec2 vertexUV;\n"
    "\n"
    "// Output data ; will be interpolated for each fragment.\n"
    "out vec2 UV;\n"
    "\n"
    "// Values that stay constant for the whole mesh.\n"
    "uniform mat4 MVP;\n"
    "\n"
    "void main(){\n"
    "\n"
    "    // Output position of the vertex, in clip space : MVP * position\n"
    "    gl_Position =  MVP * vec4(vertexPosition_modelspace,1);\n"
    "\n"
    "    // UV of the vertex. No special space for this one.\n"
    "    UV = vertexUV;\n"
    "}";

static const char * texture_frag_shader =
    "#version 300 es\n"
    "\n"
    "precision mediump float;\n"
    "// Interpolated values from the vertex shaders\n"
    "in vec2 UV;\n"
    "\n"
    "// Ouput data\n"
    "out vec3 color;\n"
    "\n"
    "// Values that stay constant for the whole mesh.\n"
    "uniform sampler2D myTextureSampler;\n"
    "\n"
    "void main(){\n"
    "\n"
    "    // Output color = color of the texture at the specified UV\n"
    "    color = texture( myTextureSampler, UV ).rgb;\n"
    "}";
class EGLApplication
{
public:
    EGLApplication(WaylandServer const & server)
        : _width(800)
        , _height(600)
        , _widthTexture(500)
        , _heightTexture(300)
        , _display(server.Display())
        , _compositor(server.Compositor())
        , _shell(server.Shell())
        , _surface(nullptr)
        , _shellSurface(nullptr)
        , _region(nullptr)
        , _eglContext()
        , _colorBackground()
        , _colorTexture()
        , _texture()
        , _textureID()
        , _vertexPosition_modelspaceID()
        , _vertexUVID()
        , _vertexbuffer()
        , _uvbuffer()
        , _matrixID()
        , _buffer(nullptr)
        , _xrot()
        , _yrot()
        , _zrot()
        , window(new struct window)
        , rotation_uniform()
        , pos()
        , col()
        , tex()
        , benchmark_time()
        , frames()
    {}
    ~EGLApplication()
    {
        if (_buffer)
            delete [] _buffer;
    }
    struct window
    {

    };

    static GLuint create_shader(struct window *window, const char *source, GLenum shader_type)
    {
        GLuint shader;
        GLint status;

        shader = glCreateShader(shader_type);
        assert(shader != 0);

        glShaderSource(shader, 1, (const char **) &source, NULL);
        glCompileShader(shader);

        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (!status) {
            char log[1000];
            GLsizei len;
            glGetShaderInfoLog(shader, 1000, &len, log);
            fprintf(stderr, "Error: compiling %s: %*s\n",
                    shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment",
                    len, log);
            exit(1);
        }

        return shader;
    }
    bool Initialize()
    {
        _surface = wl_compositor_create_surface(const_cast<wl_compositor *>(_compositor));
        if (!_surface)
        {
            cerr << "Can't create surface" << endl;
            return false;
        } else
        {
            cerr << "Created surface" << endl;
        }

        _shellSurface = wl_shell_get_shell_surface(const_cast<wl_shell *>(_shell), _surface);
        wl_shell_surface_set_toplevel(_shellSurface);

        CreateOpaqueRegion();
        if (!_eglContext.Initialize(const_cast<wl_display *>(_display)))
            return false;
        if (!_eglContext.CreateWindow(_surface, _width, _height))
            return false;

//        GLuint frag = create_shader(window, frag_shader_text, GL_FRAGMENT_SHADER);
//        GLuint vert = create_shader(window, vert_shader_text, GL_VERTEX_SHADER);
        GLuint frag_texture = create_shader(window, texture_frag_shader, GL_FRAGMENT_SHADER);
        GLuint vert_texture = create_shader(window, texture_vertex_shader, GL_VERTEX_SHADER);

        GLuint programID = glCreateProgram();
//        glAttachShader(programID, frag);
//        glAttachShader(programID, vert);
        glAttachShader(programID, frag_texture);
        glAttachShader(programID, vert_texture);
        glLinkProgram(programID);

        GLint status;
        glGetProgramiv(programID, GL_LINK_STATUS, &status);
        if (!status) {
            char log[1000];
            GLsizei len;
            glGetProgramInfoLog(programID, 1000, &len, log);
            fprintf(stderr, "Error: linking:\n%*s\n", len, log);
            exit(1);
        }

        glUseProgram(programID);

//        pos = 0;
//        col = 1;
//        tex = 1;

//        glBindAttribLocation(programID, pos, "pos");
//        glBindAttribLocation(programID, col, "color");
//        glBindAttribLocation(programID, tex, "texture");
        glLinkProgram(programID);

//        rotation_uniform =
//            glGetUniformLocation(programID, "rotation");
        _matrixID = glGetUniformLocation(programID, "MVP");

        _vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
        _vertexUVID = glGetAttribLocation(programID, "vertexUV");
        _textureID  = glGetUniformLocation(programID, "myTextureSampler");

        glGenTextures(1, _texture);
        glBindTexture(GL_TEXTURE_2D, _texture[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // When MAGnifying the image (no bigger mipmap available), use LINEAR filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        // Generate mipmaps, by the way.
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            _widthTexture,
            _heightTexture,
            0,
            GL_RGB,
            GL_FLOAT,
            NULL);
        _buffer = new GLfloat[3 * _widthTexture * _heightTexture];

        static const GLfloat g_vertex_buffer_data[6][3] = {
        { -1.0,  1.0, 0.0 },
        { -1.0, -1.0, 0.0 },
        {  1.0, -1.0, 0.0 },
        { -1.0,  1.0, 0.0 },
        {  1.0, -1.0, 0.0 },
        {  1.0,  1.0, 0.0 }
        };
        static const GLfloat g_uv_buffer_data[6][3] = {
        { 0, 1 },
        { 0, 0 },
        { 1, 0 },
        { 0, 1 },
        { 1, 0 },
        { 1, 1 }
        };
        glGenBuffers(1, &_vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        glGenBuffers(1, &_uvbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

        Draw();

        return true;
    }
    void Run()
    {
        while (wl_display_dispatch(const_cast<wl_display *>(_display)) != -1)
        {
            HandleEvents();
        }
    }
    void GetNextImage()
    {
        const int components = 3;
        _colorBackground.r += 0.01F;
        if (_colorBackground.r > 1.0F)
            _colorBackground.r -= 1.0F;
        _colorTexture.b += 0.1F;
        if (_colorTexture.b > 1.0F)
            _colorTexture.b -= 1.0F;
        int offset = 0;
        for (int y = 0; y < _heightTexture; ++y)
        {
            offset = y * _widthTexture * components;
            for (int x = 0; x < _widthTexture; ++x)
            {
                _buffer[offset + 0] = 1;
                _buffer[offset + 1] = 1;
                _buffer[offset + 2] = 1;
                offset += components;
            }
        }
    }
    void HandleEvents()
    {
        GetNextImage();
        Draw();
    }
    void Shutdown()
    {
        _eglContext.Shutdown();
        wl_display_disconnect(const_cast<wl_display *>(_display));
        cout << "disconnected from display" << endl;
    }

private:
    int _width;
    int _height;
    int _widthTexture;
    int _heightTexture;
    const wl_display * _display;
    const wl_compositor * _compositor;
    const wl_shell * _shell;
    wl_surface * _surface;
    wl_shell_surface * _shellSurface;
    wl_region * _region;
    EGLWindow _eglContext;
    GLColor _colorBackground;
    GLColor _colorTexture;
    GLuint _texture[1];
    GLuint _textureID;
    GLuint _vertexPosition_modelspaceID;
    GLuint _vertexUVID;
    GLuint _vertexbuffer;
    GLuint _uvbuffer;
    GLuint _matrixID;
    GLfloat * _buffer;
    GLfloat _xrot;
    GLfloat _yrot;
    GLfloat _zrot;
    GLfloat rtri;
    GLfloat rquad;
    struct window * window;
    GLint rotation_uniform;
    GLuint pos;
    GLuint col;
    GLuint tex;
    uint32_t benchmark_time;
    uint32_t frames;

    void CreateOpaqueRegion()
    {
        _region = wl_compositor_create_region(const_cast<wl_compositor *>(_compositor));
        wl_region_add(_region, 0, 0, _width, _height);
        wl_surface_set_opaque_region(_surface, _region);
        wl_region_destroy(_region);
    }
    void Clear()
    {
//        glClearColor(_colorBackground.r, _colorBackground.g, _colorBackground.b, _colorBackground.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void Draw()
    {
        static const GLfloat verts[6][3] = {
            { -1.0,  1.0, 0.0 },
            { -1.0, -1.0, 0.0 },
            {  1.0, -1.0, 0.0 },
            { -1.0,  1.0, 0.0 },
            {  1.0, -1.0, 0.0 },
            {  1.0,  1.0, 0.0 }
        };
//        static const GLfloat colors[6][3] = {
//            { 0, 0, 0 },
//            { 0, 0, 0 },
//            { 0, 0, 0 },
//            { 0, 0, 0 },
//            { 0, 0, 0 },
//            { 0, 0, 0 }
//        };
        static const GLfloat texture[6][3] = {
            { 0, 1 },
            { 0, 0 },
            { 1, 0 },
            { 0, 1 },
            { 1, 0 },
            { 1, 1 }
        };
        GLfloat angle;
        GLfloat rotation[4][4] = {
            { 1, 0, 0, 0 },
            { 0, 1, 0, 0 },
            { 0, 0, 1, 0 },
            { 0, 0, 0, 1 }
        };
        static const uint32_t speed_div = 5, benchmark_interval = 5;
        struct wl_region *region;
        EGLint rect[4];
        EGLint buffer_age = 0;
        struct timeval tv;

        gettimeofday(&tv, NULL);
        uint32_t time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
        if (frames == 0)
            benchmark_time = time;
        if (time - benchmark_time > (benchmark_interval * 1000)) {
            printf("%d frames in %d seconds: %f fps\n",
                   frames,
                   benchmark_interval,
                   (float) frames / benchmark_interval);
            benchmark_time = time;
            frames = 0;
        }

        angle = (time / speed_div) % 360 * M_PI / 180.0;
        rotation[0][0] =  cos(angle);
        rotation[0][2] =  sin(angle);
        rotation[2][0] = -sin(angle);
        rotation[2][2] =  cos(angle);

        glViewport(0, 0, _width, _height);

        glUniformMatrix4fv(_matrixID, 1, GL_FALSE,
                           (GLfloat *) rotation);

        glClearColor(0.0, 0.0, 0.0, 0.5);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, _texture);
        glBindTexture(GL_TEXTURE_2D, _texture[0]);

        // Give the image to OpenGL
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            _widthTexture,
            _heightTexture,
            0,
            GL_RGB,
            GL_FLOAT,
            _buffer);

        // Set our "myTextureSampler" sampler to user Texture Unit 0
        glUniform1i(_textureID, 0);

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(_vertexPosition_modelspaceID);
        glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
        glVertexAttribPointer(
            _vertexPosition_modelspaceID,  // The attribute we want to configure
            3,                            // size
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void*)0                      // array buffer offset
            );

        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(_vertexUVID);
        glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
        glVertexAttribPointer(
            _vertexUVID,                   // The attribute we want to configure
            2,                            // size : U+V => 2
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void*)0                      // array buffer offset
            );

        // Draw the triangles !
        glDrawArrays(GL_TRIANGLES, 0, 2*3); // 12*3 indices starting at 0 -> 12 triangles

        glDisableVertexAttribArray(_vertexPosition_modelspaceID);
        glDisableVertexAttribArray(_vertexUVID);

        frames++;
        SwapBuffers();
    }
    void SwapBuffers()
    {
        _eglContext.SwapBuffers();
    }
};


int main(int argc, char **argv)
{
    WaylandServer server;

    if (!server.Initialize())
        exit(1);

    EGLApplication app(server);
    if (!app.Initialize())
        exit(1);
    app.Run();
    app.Shutdown();

    exit(0);
}
