#include "core/variable.h"

#include <GL/glew.h>

namespace core
{
    GLvoid xy()
    {
        // |       |       |       |
        // | x | y | x | y | x | y |

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);
    }

    GLvoid xyz()
    {
        // |           |           |
        // | x | y | z | x | y | z |

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);
    }

    GLvoid xyrgb()
    {
        // |       |           |       |           |
        // | x | y | r | g | b | x | y | r | g | b |

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizefloat, nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizefloat, (GLvoid*)(2 * sizefloat));
        glEnableVertexAttribArray(1);
    }

    GLvoid xyzrgb()
    {
        // |           |           |           |           |
        // | x | y | z | r | g | b | x | y | z | r | g | b |

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizefloat, nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizefloat, (GLvoid*)(3 * sizefloat));
        glEnableVertexAttribArray(1);
    }

    GLvoid xyrgba()
    {
        // |       |               |       |               |
        // | x | y | r | g | b | a | x | y | r | g | b | a |

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizefloat, nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizefloat, (GLvoid*)(2 * sizefloat));
        glEnableVertexAttribArray(1);
    }

    GLvoid xyzrgba()
    {
        // |           |               |           |               |
        // | x | y | z | r | g | b | a | x | y | z | r | g | b | a |

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizefloat, nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizefloat, (GLvoid*)(3 * sizefloat));
        glEnableVertexAttribArray(1);
    }

    GLvoid xyrgbi()
    {
        // |       |              |       |              |
        // | x | y | ri | gi | bi | x | y | ri | gi | bi |

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizefloat, nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_UNSIGNED_INT, GL_FALSE, 5 * sizeuint, (GLvoid*)(2 * sizeuint));
        glEnableVertexAttribArray(1);
    }

    GLvoid xyzrgbi()
    {
        // |           |              |           |              |
        // | x | y | z | ri | gi | bi | x | y | z | ri | gi | bi |

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizefloat, nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_UNSIGNED_INT, GL_FALSE, 6 * sizeuint, (GLvoid*)(3 * sizeuint));
        glEnableVertexAttribArray(1);
    }

    GLvoid xyrgbai()
    {
        // |       |                   |       |                   |
        // | x | y | ri | gi | bi | ai | x | y | ri | gi | bi | ai |

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizefloat, nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 4, GL_UNSIGNED_INT, GL_FALSE, 6 * sizeuint, (GLvoid*)(2 * sizeuint));
        glEnableVertexAttribArray(1);
    }

    GLvoid xyzrgbai()
    {
        // |           |                   |           |                   |
        // | x | y | z | ri | gi | bi | ai | x | y | z | ri | gi | bi | ai |

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizefloat, nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 4, GL_UNSIGNED_INT, GL_FALSE, 7 * sizeuint, (GLvoid*)(3 * sizeuint));
        glEnableVertexAttribArray(1);
    }

    GLvoid xyst()
    {
        // |       |       |       |       |
        // | x | y | s | t | x | y | s | t |

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizefloat, nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizefloat, (GLvoid*)(2 * sizefloat));
        glEnableVertexAttribArray(1);
    }

    GLvoid xyzst()
    {
        // |           |       |           |       |
        // | x | y | z | s | t | x | y | z | s | t |

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizefloat, nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizefloat, (GLvoid*)(3 * sizefloat));
        glEnableVertexAttribArray(1);
    }

    GLvoid xyrgbst()
    {
        // |       |           |       |       |           |       |
        // | x | y | r | g | b | s | t | x | y | r | g | b | s | t |

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizefloat, nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizefloat, (GLvoid*)(2 * sizefloat));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizefloat, (GLvoid*)(5 * sizefloat));
        glEnableVertexAttribArray(2);
    }

    GLvoid xyzrgbst()
    {
        // |           |           |       |           |           |       |
        // | x | y | z | r | g | b | s | t | x | y | z | r | g | b | s | t |

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizefloat, nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizefloat, (GLvoid*)(3 * sizefloat));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizefloat, (GLvoid*)(6 * sizefloat));
        glEnableVertexAttribArray(2);
    }

    GLvoid xyrgbast()
    {
        // |       |               |       |       |               |       |
        // | x | y | r | g | b | a | s | t | x | y | r | g | b | a | s | t |

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizefloat, nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizefloat, (GLvoid*)(2 * sizefloat));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizefloat, (GLvoid*)(6 * sizefloat));
        glEnableVertexAttribArray(2);
    }

    GLvoid xyzrgbast() //
    {
        // |           |               |       |           |               |       |
        // | x | y | z | r | g | b | a | s | t | x | y | z | r | g | b | a | s | t |

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizefloat, nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizefloat, (GLvoid*)(3 * sizefloat));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizefloat, (GLvoid*)(7 * sizefloat));
        glEnableVertexAttribArray(2);
    }

    GLvoid xyrgbist() // xy rgbi st
    {
        // |       |              |       |       |              |       |
        // | x | y | ri | gi | bi | s | t | x | y | ri | gi | bi | s | t |

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizefloat, nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_UNSIGNED_INT, GL_FALSE, 7 * sizeuint, (GLvoid*)(2 * sizeuint));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizefloat, (GLvoid*)(5 * sizefloat));
        glEnableVertexAttribArray(2);
    }

    GLvoid xyzrgbist()
    {
        // |           |              |       |           |              |       |
        // | x | y | z | ri | gi | bi | s | t | x | y | z | ri | gi | bi | s | t |

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizefloat, nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_UNSIGNED_INT, GL_FALSE, 8 * sizeuint, (GLvoid*)(3 * sizeuint));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizefloat, (GLvoid*)(6 * sizefloat));
        glEnableVertexAttribArray(2);
    }

    GLvoid xyrgbaist()
    {
        // |       |                   |       |       |                   |       |
        // | x | y | ri | gi | bi | ai | s | t | x | y | ri | gi | bi | ai | s | t |

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizefloat, nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 4, GL_UNSIGNED_INT, GL_FALSE, 8 * sizeuint, (GLvoid*)(2 * sizeuint));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizefloat, (GLvoid*)(6 * sizefloat));
        glEnableVertexAttribArray(2);
    }

    GLvoid xyzrgbaist()
    {
        // |           |                   |       |           |                   |       |
        // | x | y | z | ri | gi | bi | ai | s | t | x | y | z | ri | gi | bi | ai | s | t |

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizefloat, nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 4, GL_UNSIGNED_INT, GL_FALSE, 9 * sizeuint, (GLvoid*)(3 * sizeuint));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizefloat, (GLvoid*)(7 * sizefloat));
        glEnableVertexAttribArray(2);
    }
}