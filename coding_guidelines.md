# Implementation guidelines

In this document, I try to collect the lessons I learn before/while/after coding. 
It mainly serves as my personal reminder and to force myself to make my thoughts more precise.

I've tried to order my thoughts in different phases and roughly in a "temporal order" as you would encounter them implementing a class.

No claim made on having the best solutions.

The last section is a list of potential traps that I try to keep in mind.

## Preparation
- *Know what you want*: I often want to do everything at once (implement this cool data structure, write that ingenious script, learn this aspect, spend time with my loved once, …). 
Time management is important for me to look back on a successful day. 
Ask yourself what you want to reach with a project. 
How much time do you want to invest? 
Are there things with high priority/that are cooler?
It's an old wisdom, do one thing at a time and do it right. 
It took me years until I finally put this advice into practice.
- *Work-Life-Balance*: It's great to be on the way to mastery. 
Don't forget your family and friends.

## Planning

- *Test your algorithm on paper*: Everybody tells you that, first think about your algorithm, then code it.
- *Edgecase overview*: If a paper is available, go through the paper and make a summary of all edge cases/strange situations your data structure could end up in. 
Implementing the general case and then realising there is a certain necessary special case, can mess up quite a lot. 
Take for example one wants to implement random real numbers in the interval `[0, 1)`. 
When compared they generate new digits until they differ. 
Sometimes one might want to compare a randomly generated number with a deterministic number (for example a `0` or `0.111…`/`1`). 
This is a common operation in treaps (for example when merging and splitting).
- *Learn from professionals*: Often somebody already solved the same or a similar problem (Especially if you're reimplementing something for the sake of learning). 
If you roughly know, what you want to do, go and look at the solutions other people came up with. 
There's nearly always a way to find the solution of an expert since there are many open-source libraries/projects out there.
In the simplest way, go and check your STL implementation. 
Many classes are templates, and so you can find big chunks of the code on your machine in the header files.
- *Take a break, explain it to somebody*: When stuck, go and drink tea or come back tomorrow. 
Getting some distance often gives your brain the chance to win a new perspective. 
Explaining your problem to someone forces you to follow one red line and make things as simple as possible (especially if the other person has no clue about computer science). 
You then often simplify this in a way you would never have done for yourself.

## Tools

- *Know your tools*: Most IDEs are very powerful, but you need to know where the buttons are. 
Same for version control systems (seriously, use one), continuous integration platforms, lints and other beautiful little gizmos.
Keep reading the tips-and-tricks pages of your favourite.

## Implementation

- *Plan what you want to code*: At least do a short draft on a piece of paper or write down some core parts in form of commented pseudo-code.
- *Start with the interface*: I prefer to start with the interface. 
It forces you to think about the operations you want to support. 
Starting with the implementation of an algorithm can lead to a lot of unnecessary refactoring. 
Another important reason is that most people will be interested in the interface when they work with your code. 
Implementation details only interest "advanced users".
- *Know the language*: This comes with experience. 
Never stop learning a language if you want to master it. 
I tend to learn a new feature (for example `noexcept`) and use it all over the place. 
That's ok, but keep an open mind and regularly check the basics. 
In our example, one would then see that putting `noexcept` blindly everywhere can lead to problems since it's part of the interface. 
If you suddenly decide to remove it, you can't since it's part of the contract. 
Going in the other direction is a lot easier, you always can add a `noexcept` and make the contract tighter on your side. 
    - [C++ FAQ](https://isocpp.org/faq)
- *Comments*: Write down your design decisions. 
Why did you solve something the way you solved it? Working out what a code does is a question of experience, time and reverse engineering skills. 
But getting the answer to a "why?" question is really hard. 
Maybe explain in one or two sentences why you prefer one solution over some other. 
Coming back after half a year and trying to fix a bug with a wrong model in mind can cost you a lot of time.
- *Can I do better?*: After implementing and showing that some code works, take a step back and study what you've written. 
Is this the best code I can produce? 
Is there a simpler way of approaching the problem? 
That's not necessarily the same as thinking about the best algorithm but might include using specialities of the language. 
Take as an example a linked list, assume you want to iterate through it, maybe deleting a node `x`. 
The algorithm is pretty straightforward, just follow the pointers and change them as necessary when node `x` is found. 
One way to implement this is by storing the parent in an additional variable and updated it each time you advance one node. 
Another way is to use a pointer to a pointer (the field of the parent that points to the active node). 
Both are valid solutions, but I prefer the double pointer method since it has less special cases. 
An alternative might be to use a root dummy node. 
- *Know when to use OOP and when procedural*: There's a trade-off between complexity and encapsulation. Complexity obviously is complex, you need to sit down and think about what's going on. Encapsulation can inflate your code and make it even harder to understand if used in to fine scale. [Object-Oriented Programming is Bad](https://www.youtube.com/watch?v=QM1iUe6IofM)

## Testing

- *Do unit-testing*: I'm a big fan of testing. 
First reason is, it makes debugging a lot easier. 
If you know a certain value triggers a bug; you typically need to start your application and create the exact situation such that the bug is triggered. 
This can be time-consuming. 
If your code is unit testable, tracking a bug down is a matter of one additional test.
- *Don't over-do testing*: Testing is important. 
As a personal tendency, it seems like I put too many test cases, which makes changing code hard. 
Still working on finding the perfect balance …

## Cleanup

- *Is it complete?*: Having many goals in life, some (especially private) projects tend to be done under time pressure or in small chunks of time scattered here and there (on the train to work, while waiting for the spaghetti-water to get hot, …). 
Per se, that's often not a problem. 
At least take your time before committing to make sure you've done every change you intended to do and nothing is missing.
- *Write descriptive comments with context*: Imagine: The first thing somebody sees of your code, is the HTML documentation for your class. 
If a variable is called `alarmSettings`, don't comment it with `settings for the alarm`. 
Try to give something more descriptive like `allows to set alarm attributes like date, time and duration, for a complete list of possible values see xxx.` 
It gives no new information. 
Tell the user what it's for and in the best case give a hint where the bigger picture is explained. 
(Don't over-do it, a link/reference to a paper or some well-chosen keywords in the class description might be sufficient.)
- *Use Lint and similar tools*: Yes, coding style helps to understand code. 
Honestly, I don't care if I write an `if` with or without a space between parenthesis (`if(){}` <-> `if () {}`). 
I normally turn those hints off if they conflict with my personal style (consistency is important, not the actual choice).
Let the computer be your teacher, and let it show you style issues that can cause serious bugs. 
The problem zones of a language are well known, and solutions are often easy. 
One of my favourite examples is `==` and `===` in JavaScript, both work, but `===` clearly leads to fewer bugs since it's closer to the intuition.
- *Have a personal checklist*: Everybody has his/her weaknesses.
Use a checklist for things you know you tend to get wrong.

## Feedback

- *Ask people their opinion*: There's only so much you can do in your bubble, and there's nothing more valuable than a second opinion.
Take every advice seriously (from whoever it comes from); 
Think careful about it, discuss it and finally accept or reject it.
Make sure it's your reason that decides and not your hurt ego.


## My C++ Quality Checklist
Some things I've encountered that weren't obvious to me at the time.

- Assignment operator returns `*self` as reference. [isocpp FAQ](https://isocpp.org/wiki/faq/coding-standards#lint-guidelines)
- Having any virtual method requires having a virtual destructor. [isocpp FAQ](https://isocpp.org/wiki/faq/coding-standards#lint-guidelines)
- implement all five if at least one is needed: destructor, copy assignment operator, copy constructor, move assignment operator, move constructor [isocpp FAQ](https://isocpp.org/wiki/faq/coding-standards#lint-guidelines)
- use initialization lists rather than assignment [isocpp FAQ](https://isocpp.org/wiki/faq/coding-standards#lint-guidelines)
- check for danger of self assignment or other cases where an object is passed to itself [isocpp FAQ](https://isocpp.org/wiki/faq/coding-standards#lint-guidelines), [isocpp FAQ](https://isocpp.org/wiki/faq/assignment-operators#self-assignment-what)
- carefull about placing `noexcept`
- <cite>a C++ byte might have more than 8 bits</cite> [isocpp FAQ](https://isocpp.org/wiki/faq/intrinsic-types#bits-per-byte): mostly from old times or today in low-level systems relevant??
- difference `std::endl` and `'\n'`: `std::endl` also flushes (`std::flush`) [isocpp FAQ](https://isocpp.org/wiki/faq/input-output#endl-vs-slash-n)
- correctly use printing of classes: `friend operator<<()` and `printOn()` [isocpp FAQ](https://isocpp.org/wiki/faq/input-output#output-operator-via-friends)
- Use `/` as path separator [isocpp FAQ](https://isocpp.org/wiki/faq/input-output#backslashes-in-filenames)
- `X& const x` is nonsense, references are always constant. [isocpp FAQ](https://isocpp.org/wiki/faq/const-correctness#const-ref-nonsense)
- Make sure to return const references (to members) from constant methods. `const X& f() const;` (not `X& f() const;`), the compiler might not always catch this. [isocpp FAQ](https://isocpp.org/wiki/faq/const-correctness#return-const-ref-from-const-memfn)
- Distinguish logical and physical state, first design the logical state. [isocpp FAQ](https://isocpp.org/wiki/faq/const-correctness#logical-vs-physical-state)
- Use `const` depending on the object's logical state. [isocpp](https://isocpp.org/wiki/faq/const-correctness#logical-vs-physical-const)
- <cite>A reference is the object. It is not a pointer to the object, nor a copy of the object. It is the object.</cite> [isocpp FAQ](https://isocpp.org/wiki/faq/references#overview-refs)
- `new` can throw exceptions. [cplusplus](http://www.cplusplus.com/reference/new/operator%20new/)
- use `unique_ptr` instead of raw pointers
- Members and base classes of a `struct` are `public` by default, for `class` they default to `private`. [isocpp FAQ](https://isocpp.org/wiki/faq/classes-and-objects#struct-vs-class)
- `const` vs. `constexpr`: [stackoverflow](http://stackoverflow.com/questions/14116003/difference-between-constexpr-and-const)

    **objects**:
    
    - `const`: value of object won't change (promise not to change)
    - `constexpr`: fit for use in a constant expression (evaluation possible at compile time)
    
    **functions**:
    
    - `const`: only for non-static member functions: no logical state change.
    - `constexpr`: function fit for use in constant expressions (non-virtual, one return, typedefs, static asserts, …; see [isocpp: Relaxin constraints](https://isocpp.org/blog/2013/04/n3652-relaxing-constraints-on-constexpr-functions))

    **general**:
    
    - `const`: no logical state change allowed
    - `constexpr`: use in constexpr -> Evaluation at compile time possible

    **use in constant expressions**:
    
    - `const`: only for initialized literal/enumeration types; never functions
    - `constexpr`: the very definition; functions need to be marked constexpr

    **object declaration**:
    
    - `constexpr` implies `const`
    
    **member function declaration**:
    
    - Use both `constexpr` and `const`.

- Use `{}` for initialization. [isocpp FAQ](https://isocpp.org/wiki/faq/cpp11-language#uniform-init)
- Use `explicit` for constructors and operators. [isocpp FAQ](https://isocpp.org/wiki/faq/ctors#explicit-ctors)
- Given by default to a class: [isocpp FAQ](https://isocpp.org/wiki/faq/ctors)
    
    - copy constructor: copies all elements
    - copy assignment: copies all elements
    - move constructor: moves all elements
    - move assignment: moves all elements

- Local objects are destructed in reversed construction order. [isocpp FAQ](https://isocpp.org/wiki/faq/dtors#order-dtors-for-locals)
- Destructors always automagically destruct members. [isocpp FAQ](https://isocpp.org/wiki/faq/dtors#calling-member-dtors)
- Destructors automagically call inherited destructors. [isocpp FAQ](https://isocpp.org/wiki/faq/dtors#calling-base-dtor)
- Distinguish between operators defined as functions and defined as members. [isocpp FAQ: point 7](https://isocpp.org/wiki/faq/operator-overloading#op-ov-rules)
- auto-generation of constructor/destructor/etc.: [stackoverflow](http://stackoverflow.com/questions/4943958/conditions-for-automatic-generation-of-default-copy-move-ctor-and-copy-move-assi)  
u. d.: user-declared

	| auto-generated           | if                   |
	| -----------------------: |:---------------------|
	| default constructor      | no u. d. constructor |
	| copy constructor         | no u. d. move constructor or move assignment operator |
	| copy assignment operator | no u. d. move constructor or assignment operator |
	| destructor               | no u. d. destructor  |
	| move constructor         | no u. d. copy constructor, copy assignment operator or destructor |
	| move assignment operator | no u. d. copy constructor, copy assingment operator or destructor |
- Careful about the One-Definition Rule. [Andrzej's C++ blog](https://akrzemi1.wordpress.com/2016/11/28/the-one-definition-rule/)
- Interface design: Don't surprise your users.
- Definition substitutability: <cite>the derived class is allowed (not required) to add (not remove) public methods, and for each public method inherited from the base class, the derived class is allowed (not required) to weaken preconditions and/or strengthen postconditions (not the other way around). Further the derived class is allowed to have completely different constructors, static methods, and non-public methods.</cite> [isocpp FAQ](https://isocpp.org/wiki/faq/proper-inheritance#circle-ellipse-behavior)
- Know the trade-off with defensive checks (bad for static analyzers <-> good for robust coding) [Andrzej's C++ blog](https://akrzemi1.wordpress.com/2016/12/12/concealing-bugs/)
- [CppCon Talk: Argue(ments)](https://www.youtube.com/watch?v=ZbVCGCy3mGQ): 
    Semantics of most common argument types, all other cases are very rare/don't make sense.

| Type                             | Description        |
| -------------------------------: |:------------------ |
| `T`                              | Snapshot           |
| `T const &`                      | Observe |
| `T const *`                      | Observe optional |
| `T &`                            | Modify |
| `T *`                            | Modfiy optional |
| `T &&`                           | Sink, Transfer Ownership |
| `unique_ptr<T>`                  | Sink, Transfer Ownership |
| `unique_ptr<T const>`            | Sink, Transfer Ownership |
| `shared_ptr<T>`                  | Share ownership |
| `shared_ptr<T const>`            | Share ownership |
| `shared_ptr<T> const &`          | Optionally Transfer Ownership |
| `shared_ptr<T const> const &`    | Optionally Transfer Ownership |
| `unique_ptr<T>&`                 | Reseat |
| `unique_ptr<T const>&`           | Reseat |
| `shared_ptr<T>&`                 | Reseat |
| `shared_ptr<T const>&`           | Reseat |

- Pass by Value when you can, pass by `const` reference when you must. Use profiling and benchmarking to decide. [CppCon Talk: Argue(ments)](https://www.youtube.com/watch?v=ZbVCGCy3mGQ)


