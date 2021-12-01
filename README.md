# XML-editor
A university project for Data structures and Algorithms course; CSE331s

## Project Description 
XML (Extensible Markup Language) is one of the most famous formats for storing and sharing
information among different devices. Some text editors such as Sublime Text are able to parse
such files and do some basic operations. In this project, you will work on developing a GUI
(Graphical User Interface) based program to parse and visualize an XML file.
In our system the XML file will represent users in a social network
Each user has id (unique), name, list of posts, list of followers.
Each post has text and list of topics

### Project Requirements 

1. Building a GUI in which the user can specify the location of an input XML file.
2. Checking the XML consistency: The input XML may have inconsistencies like missing any
of the closing and opening tags or not matching tags.The program should be able to detect
and visually show any errors in consistency. Optimally, the program will also be able to
automatically solve the errors.
3. Formatting (Prettifying) the XML: the XML file should be well formatted by keeping the
indentation for each level.
4. Converting XML to JSON: JSON (Javascript Object Notation) is another format that is used
to represent data. It’s helpful to convert the XML into JSON, especially when using
javascript as there’s tons of libraries and tools that use json notation.
5. Minifying the XML file: Since spaces and newlines (\n) are actually characters that can
increase the size of an XML document. This feature should aim at decreasing the size of
an XML file (compressing it) by deleting the whitespaces and indentations.
6. Compressing the data in the XML/JSON file: You should come-up with a way to reduce the
size of the file using a data compression technique. You can invent your own ad-hoc
method for such compression. On the other hand, you can check how JSONH works and
try to distill ideas from it. Finally, you can use a data compression technique such as byte
pair encoding (https://en.wikipedia.org/wiki/Byte_pair_encoding).
The smaller the output file is, the more efficient your algorithm is.
7. representing the users data using the graph data structure: the XML file will represent the
users data in a social network (their posts, followers, ...etc).
The user data is his id (unique across the network), name, list of his posts and followers.
So you should represent the relation between the followers using the graph data
structure as it will be very helpful for the network analysis.
If the input file was like this (the dots mean that there are additional tags inside the user
tag) :
Then you should build a graph relation between the user that looks like the graph
beneath.
8. Network analysis: by representing the network using the graph data structure, we can
extract some important data:
- who is the most influencer user (has the most followers)
- who is the most active user (connected to lots of users)
- the mutual followers between 2 users
- for each user, suggest a list of users to follow (the followers of his followers)
8. Post search: given a specific word or topic, get the posts where this word or topic was
mentioned.

### Bonus Requirements 
1. Graph visualization: you’re free to use any tool or 3rd party library to help you visualize the
graph of the network showing how the user is connected to each other.
2. Additional operations: you’re free to implement additional operations to help you analyze
the network better.


-----------
# Project Implementation 
## Libraries
We are going to use the QT library to generate the GUI of the application.
