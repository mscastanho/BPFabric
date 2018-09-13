# msSFC: Multi-Stage Service Function Chaining

This modification of the original BPFabric project implements a distributed
variation of the components of RFC 7665, which specifies a reference service
function chaining architecture.

Forwarding and proxy functionalities are distributed over each SF, which are now
composed of 4 "stages", configured as a pipeline:

pkt in -> Decap -> SF -> Encap -> Forwarding -> pkt out

By using this approach, there is no need for separate Proxy and SFF elements,
all service functions (whose functionality is actually implemented in the SF
stage) can be NSH-unaware, with encap/decap operations being performed 
transparently by the Decap and Encap stages using simple pointer arithmetic.

This reduces the overhead of encap/decap operations and allows perfect matching
between inbound and outbound packets without the need of tables or complex schemes. 
Since the underlying switch application (which coordinates the execution of each 
stage) always has the pointer to the packet being processed, the SF stage can make 
any kind of changes it wants to the original packet, as long as the original pointer 
is used.
