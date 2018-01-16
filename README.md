# 2081 Software Coding Standards

Follow the Google C++ guide found at
[*https://google.github.io/styleguide/cppguide.html*](https://google.github.io/styleguide/cppguide.html)
unless otherwise specified. If you have questions, ask a person who does
code reviews for the team.

## IMPORTANT SECTIONS

[*https://google.github.io/styleguide/cppguide.html\#Naming*](https://google.github.io/styleguide/cppguide.html#Naming)

[*https://google.github.io/styleguide/cppguide.html\#Comments*](https://google.github.io/styleguide/cppguide.html#Comments)

[*https://google.github.io/styleguide/cppguide.html\#Conditionals*](https://google.github.io/styleguide/cppguide.html#Conditionals)

[*https://google.github.io/styleguide/cppguide.html\#Class\_Format*](https://google.github.io/styleguide/cppguide.html#Class_Format)

[*https://google.github.io/styleguide/cppguide.html\#Functions*](https://google.github.io/styleguide/cppguide.html#Functions)

[*https://google.github.io/styleguide/cppguide.html\#Static\_and\_Global\_Variables*](https://google.github.io/styleguide/cppguide.html#Static_and_Global_Variables)

## ADDITIONS

No magic numbers:

```C++
// 7 is a magic number. What is 7? Why is it 7? Make a enum, variable, or
// const and use that instead.
if (voltage == 7)
{  
  DoSomething();
}

// Using the variable name makes reading code easier
const int motor_overload_point = 7;

if (voltage == motor_overload_point)
{
  DoSomething();
}
```

## IMPORTANT CLARIFICATIONS/CHANGES

Text in red is the point being clarified or changed. The green text is
the clarification or change

```diff
- File.cc

+ Use File.cpp instead. The file endings that will be used are .h for
+ headers, and .cpp for source files
```

```diff
- Variables needed for if, while and for statements should normally be
- declared within those statements, so that such variables are confined to
- those scopes. E.g.:
- while (const char* p = strchr(str, '/')) str = p + 1;

+ If a variable would be used more than once per software loop,
+ declare/update it once in the same location as the other variables.
+ Otherwise, follow the above rule.
```

```diff
- Do not define implicit conversions. Use the explicit keyword for
- conversion operators and single-argument constructors.

+ Implicit conversions are OK
```

```diff
- Use C++-style casts like static_cast<float>(double_value), or brace
- initialization for conversion of arithmetic types like int64 y =
- int64{1} << 42. Do not use cast formats like int y = (int)x or int y =
- int(x) (but the latter is okay when invoking a constructor of a class type).

+ Do not use static_cast<[type]> unless absolutely necessary
```

```diff
- Enumerators (for both scoped and unscoped enums) should be named either
- like constants or like macros: either kEnumName or ENUM_NAME.

+ Use the second option only
```

```diff
- Every file should contain license boilerplate. Choose the appropriate
- boilerplate for the license used by the project (for example, Apache
- 2.0, BSD, LGPL, GPL). If you make significant changes to a file with an
- author line, consider deleting the author line.

+ This is level of complexity is unnecessary. Instead, start each header
+ with "Written by [name] for the Icarus 2081 [year] robot.
```

```diff
- Use only spaces, and indent 2 spaces at a time.

+ Use 4 spaces instead, no tabs
```

## CHECKLIST

 - [ ] Follows naming conventions

 - [ ] No magic numbers

 - [ ] Proper commenting

 - [ ] Proper file extensions

 - [ ] Proper conversions

 - [ ] Proper indentations

 - [ ] Proper header usage

 - [ ] Proper use of functions

 - [ ] Proper static and global usage

 - [ ] Proper namespace usage

 - [ ] Safe pointer usage (**Matthew will check**)

 - [ ] Concise functions

 - [ ] Compiles (discounting Eclipse issues)

 - [ ] Has been tested on testbed or robot

 - [ ] Correct line length
