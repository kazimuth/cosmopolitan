(defconst cosmo-c-keywords-regex
  (let (
        
        ;;         (kar
        ;;          '("case"
        ;;            "do"
        ;;            "return"
        ;;            "struct"
        ;;            "for"
        ;;            "default"
        ;;            "auto"
        ;;            "while"
        ;;            "else"
        ;;            "break"
        ;;            "union"
        ;;            "switch"
        ;;            "continue"
        ;;            "extern"
        ;;            "sizeof"
        ;;            "if"
        ;;            "goto"))

        ;; (ansi
        ;;  '("static"
        ;;    "sizeof"
        ;;    "if"
        ;;    "typedef"
        ;;    "const"
        ;;    "struct"
        ;;    "for"
        ;;    "union"
        ;;    "switch"
        ;;    "volatile"
        ;;    "do"
        ;;    "return"
        ;;    "goto"
        ;;    "auto"
        ;;    "enum"
        ;;    "else"
        ;;    "break"
        ;;    "extern"
        ;;    "case"
        ;;    "default"
        ;;    "register"
        ;;    "while"
        ;;    "continue"))

        (c99
         '("inline"
           "restrict"
           "_Imaginary"
           "_Bool"
           "_Pragma"
           "_Complex"))

        (c11
         '("_Atomic"
           "_Alignas"
           "_Alignof"
           "_Noreturn"
           "_Generic"
           "_Thread_local"
           "_Static_assert"
           "_Complex_I"
           "_Imaginary_I"))

        ;; (cxx17
        ;;  '("this"
        ;;    "thread_local"
        ;;    "private"
        ;;    "catch"
        ;;    "export"
        ;;    "operator"
        ;;    "sizeof"
        ;;    "dynamic_cast"
        ;;    "static_assert"
        ;;    "const_cast"
        ;;    "const"
        ;;    "for"
        ;;    "static_cast"
        ;;    "union"
        ;;    "namespace"
        ;;    "switch"
        ;;    "virtual"
        ;;    "class"
        ;;    "alignas"
        ;;    "continue"
        ;;    "volatile"
        ;;    "template"
        ;;    "mutable"
        ;;    "if"
        ;;    "public"
        ;;    "friend"
        ;;    "do"
        ;;    "inline"
        ;;    "return"
        ;;    "goto"
        ;;    "alignof"
        ;;    "auto"
        ;;    "enum"
        ;;    "typedef"
        ;;    "else"
        ;;    "break"
        ;;    "constexpr"
        ;;    "new"
        ;;    "extern"
        ;;    "using"
        ;;    "throw"
        ;;    "asm"
        ;;    "case"
        ;;    "typeid"
        ;;    "decltype"
        ;;    "reinterpret_cast"
        ;;    "default"
        ;;    "noexcept"
        ;;    "register"
        ;;    "nullptr"
        ;;    "try"
        ;;    "typename"
        ;;    "while"
        ;;    "protected"
        ;;    "static"
        ;;    "explicit"
        ;;    "delete"))

        (cosmo
         '("__rbx"
           "__msabi"
           "microarchitecture"
           "targetclones"
           "winstruct"
           "testonly"
           "forcealignargpointer"
           "textexit"
           "externinline"
           "noinline"
           "donothing"
           "byanymeansnecessary"
           "threadlocal"
           "printfesque"
           "flattenout"
           "mallocesque"
           "vallocesque"
           "null"
           "paramsnonnull"
           "returnspointerwithnoaliases"
           "alignas"
           "nosideeffect"
           "decltype"
           "forceinline"
           "nocallersavedregisters"
           "nothrow"
           "nooptimize"
           "optimizesize"
           "optimizespeed"
           "alignof"
           "relegated"
           "antiquity"
           "memcpyesque"
           "libcesque"
           "artificial"
           "returnstwice"
           "returnsaligned"
           "noprune"
           "reallocesque"
           "nullterminated"
           "unreachable"
           "hidden"
           "privileged"
           "hasatleast"
           "nodebuginfo"
           "frownedupon"
           "noreturn"
           "initarray"
           "mayalias"
           "noinstrument"
           "interruptfn"
           "nocallback"
           "textstartup"
           "warnifused"
           "attributeallocsize"
           "attributeallocalign"
           "nodiscard"
           "nointerpose"
           "compatfn"
           "returnsnonnull"
           "strftimeesque"
           "firstclass"
           "preinitarray"
           "scanfesque"
           "pureconst"
           "thatispacked"
           "strlenesque"
           "textwindows"
           "aligned"
           "typeof"
           "textreal"
           "autotype"
           "_Section"
           "_Vector_size"))

        (gnu
         '("__inline"
           "__alignof"
           "__typeof"
           "__restrict"
           "__const__"
           "__label__"
           "__noinline__"
           "__noclone__"
           "__force_align_arg_pointer__"
           "__always_inline__"
           "__gnu_inline__"
           "__alignof__"
           "__asm__"
           "__attribute__"
           "__auto_type"
           "__byte__"
           "__complex__"
           "__imag__"
           "__may_alias__"
           "__noreturn__"
           "__packed__"
           "__pointer__"
           "__printf__"
           "__real__"
           "__restrict__"
           "__scanf__"
           "__strfmon__"
           "__strftime__"
           "__strong__"
           "__target__"
           "__transparent_union__"
           "__typeof__"
           "__volatile__"
           "__word__"
           "__alias__"
           "__aligned__"
           "__alloc_align__"
           "__alloc_size__"
           "__artificial__"
           "__assume_aligned__"
           "__cold__"
           "__constructor__"
           "__destructor__"
           "__copy__"
           "__deprecated__"
           "__error__"
           "__warning__"
           "__externally_visible__"
           "__flatten__"
           "__format__"
           "__gnu_format__"
           "__gnu_printf__"
           "__gnu_scanf__"
           "__format_arg__"
           "__hot__"
           "__ifunc__"
           "__interrupt__"
           "__interrupt_handler__"
           "__leaf__"
           "__no_caller_saved_registers__"
           "__malloc__"
           "__no_icf__"
           "__no_instrument_function__"
           "__no_profile_instrument_function__"
           "__no_reorder__"
           "__no_sanitize__"
           "__no_sanitize_address__"
           "__no_address_safety_analysis__"
           "__no_sanitize_thread__"
           "__leaf__"
           "__no_sanitize_undefined__"
           "__no_split_stack__"
           "__no_stack_limit__"
           "__noclone__"
           "__noipa__"
           "__nonnull__"
           "__noplt__"
           "__nothrow__"
           "__optimize__"
           "__pure__"
           "__patchable_function_entry__"
           "__returns_nonnull__"
           "__returns_twice__"
           "__section__"
           "__sentinel__"
           "__simd__"
           "__target_clones__"
           "__unused__"
           "__used__"
           "__visibility__"
           "__warn_unused_result__"
           "__params_nonnull__"
           "__weak__"
           "__vector_size__"
           "__mode__"))

        (clang
         '("__optnone__"
           "__nodebug__"))

        )
    (concat "\\_<"
            (regexp-opt (append ;; kar
                         ;; ansi
                         ;; c99
                         c11
                         ;; cxx17
                         gnu
                         clang
                         cosmo))
            "\\_>")))

(provide 'cosmo-c-keywords)
