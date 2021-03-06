/*******************************************************************

    PROPRIETARY NOTICE

These coded instructions, statements, and computer programs contain
proprietary information of eComCloud Object Solutions, and they are
protected under copyright law. They may not be distributed, copied,
or used except under the provisions of the terms of the Source Code
Licence Agreement, in the file "LICENCE.md", which should have been
included with this software

    Copyright Notice

    (c) 2021 eComCloud Object Solutions.
        All rights reserved.
********************************************************************/

#ifndef ECI_HH_
#define ECI_HH_

#include <string>

struct InstanceName
{
    std::string type, svc, nst;

    /**
     * Construct from a string \p fullName, parsed as such:
     *
     * InstanceName ::= Type Svc Inst ;
     * Type ::= (identifier "$") | epsilon ;
     * Svc ::= [type] identifier ;
     * Nst ::= identifier ;
     *
     * The type specifier is, if unspecified, "none".
     */
    InstanceName(std::string fullName);
};

#endif