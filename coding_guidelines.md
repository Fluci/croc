# Implementation guidelines

In this document, I try to collect the lessons I learn before/while/after coding. 
It mainly serves as my personal reminder and to force myself to make my thoughts more precise.

I've tried to order my thoughts in different phases and roughly in a "temporal order" as you would encounter them implementing a class.

No claim made on having the best solutions.

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


## Testing

- *Do unit-testing*: I'm a big fan of testing. 
First reason is, it makes debugging a lot easier. 
If you know a certain value triggers a bug; you normally need to start your application and create the exact situation such that the bug is triggered. 
This can be time-consuming. 
If your code is unit testable, tracking a bug down is a matter of one additional test.
- *Don't over-do testing*: Testing is important. 
As a personal tendency, it seems like I put too many test cases, which makes changing code hard. 
Still working on finding the perfect balance …

## Cleanup

- *Write descriptive comments with context*: Imagine: The first thing somebody sees of your code, is the HTML documentation for your class. 
If a variable is called `alarmSettings`, don't comment it with `settings for the alarm`. 
Try to give something more descriptive like `allows to set alarm attributes like date, time and duration, for a complete list of possible values see xxx.` 
It gives no new information. 
Tell the user what it's for and in the best case give a hint where the bigger picture is explained. 
(Don't over-do it, a link/reference to a paper or some well-chosen keywords in the class description might be sufficient.)
- *Use Lint and similar tools*: Yes, coding style helps to understand code. 
Honestly, I don't care if I write an `if` with or without a space between parenthesis (`if(){}` <-> `if () {}`). 
I normally turn those hints off if they conflict with my personal style (consistency is important, not the concrete choice).
Let the computer be your teacher, and let it show you style issues that can cause serious bugs. 
The problem zones of a language are well known, and solutions are often easy. 
One of my favourite examples is `==` and `===` in JavaScript, both work, but `===` clearly leads to fewer bugs since it's closer to the intuition.

## Feedback

- *Ask people their opinion*: There's only so much you can do in your bubble, and there's nothing more valuable than a second opinion.
Take every advice serious (from whoever it comes from); 
Think careful about it, discuss it and finally accept or reject it.
Make sure it's your reason that decides and not your hurt ego.


