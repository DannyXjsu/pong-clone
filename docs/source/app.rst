===========
Application
===========

Abstraction layer for SDL3.

Declarations
============

Macros
------
.. c:automacro:: WINDOW_TITLE
   :file: app.h


.. c:automacro:: WINDOW_WIDTH
   :file: app.h

.. c:automacro:: WINDOW_HEIGHT
   :file: app.h

Variables
---------
.. c:autovar:: previous_time
   :file: app.h

.. c:autovar:: current_time
   :file: app.h

.. c:autovar:: pause
   :file: app.h

Functions
---------
.. c:autofunction:: app_initialize
   :file: app.h

**Definition:**

.. literalinclude:: ../../src/app.c
   :language: c
   :start-after: app_initialize
   :end-before: }

**************************************

.. c:autofunction:: app_handle_inputs
   :transform: napoleon
   :file: app.h

**Definition:**

.. literalinclude:: ../../src/app.c
   :language: c
   :start-after: app_handle_inputs
   :end-before: }

**************************************

.. c:autofunction:: app_process
   :file: app.h

**Definition:**

.. literalinclude:: ../../src/app.c
   :language: c
   :start-after: app_process
   :end-before: }

**************************************

.. c:autofunction:: app_render
   :transform: napoleon
   :file: app.h

**Definition:**

.. literalinclude:: ../../src/app.c
   :language: c
   :start-after: app_render
   :end-before: }

**************************************

.. c:autofunction:: app_finalize
   :file: app.h

**Definition:**

.. literalinclude:: ../../src/app.c
   :language: c
   :start-after: app_finalize
   :end-before: }
