# BPFabric_SFC

This modification of the original BPFabric project implements a distributed
variation of the components of RFC 7665, which specifies a reference service
function chaining architecture.

Forwarding and proxy functionalities are distributed over each SF, which are now
composed of 4 "stages", configured as a pipeline:

pkt in -> Decap -> SF -> Encap -> Forwarding -> pkt out

By using this approach, there is no need for separate Proxy and SFF elements,
all service functions (whose functionality is actually implemented in the SF
stage) can be NSH-unaware, with encap/decap operations being performed transpar$
by the Decap/Encap stage as simple pointer arithmetic operations.

This reduces the overhead of encap/decap operations and allows perfect proxy
matching without the need of tables or complex schemes. Since the underlying
switch application (which coordinates the execution of each stage) ways has the
pointer to the packet being processed, the SF stage can make any kind of change$
to the original packet, as long as the original pointer is used.
