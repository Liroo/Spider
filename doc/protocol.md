
Spider Project
Pierre MONGE
September 2017

SPIDER PROTOCOL

INTRODUCTION

The spider protocol provide a way to communicate between client and server.
Spider client is used to send logs to server. Spider server can change the behavior of client based on his status. This protocol is used to define all those things.
OVERVIEW
This is a connection based application on Boost ASIO. Behind Boost ASIO is implemented a TCP connections.
The spider protocol is so basicly a TCP connection, furthermore we have to implement a SSL security.  This protocol will not describe what kind of information will receive and send a spider server because he could get multiple usage.

As the Spider client is an Epitech project, we will at least describe some mandatory requests.
SERVER REQUEST FORMAT
The server will send to clients simple text response of the form:

	<action name> [[info_1] [info_2] ...]

Where:
Action name: is the name of the action such as "MOUSE", "KEY", etc…
Info_x: is the info needed by the action name
The client can answer by any text.

If action name is unknown by the client, the client will answer:

	UNKNOWN

That the server will not sending it again.

The server request is useful to check the status of the client but can be used to change behavior of the client.
CLIENT REQUEST FORMAT
The server will receive simple text request of the form:

	<action name> [[info_1] [info_2] ...] ['\n']
	[<action name> [[info_1] [info_2] ...] ['\n']] …

Where:
Action name: is the name of the action such as "MOUSE", "KEY", etc…
Info_x: is the info needed by the action name
The server will answer by a simple text as:

	OK

If the request is well treated,

	KO

If the request failed. The request could failed if there is a problem with the database. Or:

	UNKNOWN

If the action name is not recognized that the client will know the server did not know this action and will not send it again.
ADVICE
We advice to develop server and client with plug-in. That a plug-in can be used on the server and the client at the same time.

What is the point to use plug-in ?

A plug-in will handle one or different action name, treat the request and send the response or continue to the next plug-in.
An example to how to implement a plugin is to use:

Core.use(plugin)

Where:
plugin: is a function that will take three parameters:

	Func (req, res, next)

Req is the request itself, res is the class where you can send the response and next is the function to pass over the next plug-in.

The plug-in system permit to dev each part of the server independently.
PLUG-IN (ACTION SAMPLE)

KeyRecord:
	Client: KEY <nb of key>
	Server: Out a log

MouseRecord:
	Client: MOUSE <nb of key> [coordinate]
	Server: Out a log

OpenSSL:
	Client + Server: handshake at first connection



AUTHOR'S ADDRESS

		Pierre MONGE
		France
		76 Rue Notre Dame, Bordeaux 33000

		Phone: (+33) 618-543-548
		Email: liroo.pierre@gmail.com
