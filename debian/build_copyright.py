#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2018 Giovanni Mascellani <gio@debian.org>
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. Neither the name of the University nor the names of its contributors
#    may be used to endorse or promote products derived from this software
#    without specific prior written permission.

# THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.

# Simple and very "heuristic" script to automatically figure out the
# license and copyright holders for the files distributed with
# Boost. To execute, simply go to the Boost directory and give:
#   find -type f | ./build_copyright.py

import sys
import os
import magic
import re
import stat

#BSL_RE = re.compile(b'([dD]istributed under|[sS]ubject to) (the )?[bB]oost [sS]oftware [lL]icense, Version 1\\.0|[uU]se,? modification,? and distribution (is|are) subject to the [bB]oost [sS]oftware [lL]icense,? [vVQ]ersion 1\\.0')
BSL_RE = re.compile(b'[bB]oost [sS]oftware [lL]icense,? ?(- )?([vVQ]ersion )?1\\.0?')

LIC_RES = {'BSL': BSL_RE}

OTHER_LICS = [
    b'Permission to copy, use, modify, sell and distribute this software is granted provided this copyright notice appears in all copies. This software is provided "as is" without express or implied warranty, and with no claim as to its suitability for any purpose.',
    b'Permission to use, copy, modify, distribute and sell this software and its documentation for any purpose is hereby granted without fee, provided that the above copyright notice appear in all copies and that both that copyright notice and this permission notice appear in supporting documentation.',
    b'Permission is granted to anyone to use this software for any purpose on any computer system, and to redistribute it freely, subject to the following restrictions: 1. The author is not responsible for the consequences of use of this software, no matter how awful, even if they arise from defects in it. 2. The origin of this software must not be misrepresented, either by explicit claim or by omission. 3. Altered versions must be plainly marked as such, and must not be misrepresented as being the original software.',
    b"This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software. Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions: 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required. 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software. 3. This notice may not be removed or altered from any source distribution.",
    b'All rights reserved. THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED OR IMPLIED. ANY USE IS AT YOUR OWN RISK. Permission is hereby granted to use or copy this program for any purpose, provided the above notices are retained on all copies. Permission to modify the code and to distribute modified code is granted, provided the above notices are retained, and a notice that the code was modified is included with the above copyright notice.',
    b'Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, andor sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.',
    b'THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED OR IMPLIED. ANY USE IS AT YOUR OWN RISK. Permission is hereby granted to use or copy this program for any purpose, provided the above notices are retained on all copies. Permission to modify the code and to distribute modified code is granted, provided the above notices are retained, and a notice that the code was modified is included with the above copyright notice.',
    b'Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, andor sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.',
    b'All rights reserved. THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED OR IMPLIED. ANY USE IS AT YOUR OWN RISK. Permission is hereby granted to copy this code for any purpose, provided the above notices are retained on all copies.',
]

FILES = {}

TRIVIAL_COPYRIGHT_RE = re.compile(b'.*[cC]opyright.*')
COPYRIGHT_RE = re.compile(b'.*[cC]opyright *([(][cC][)]|\xa9|&#169;)? *([0-9][-0-9, ]*[0-9]) *:?,? *([^ ].*[^].]).*')
COPYRIGHT2_RE = re.compile(b'.*[cC]opyright *([(][cC][)]|\xa9|&#169;)? *([^ ].*[^-0-9, ]) *,? *([0-9][-0-9 ]*[0-9]).*')
COPYRIGHT3_RE = re.compile(b'.*[cC]opyright *([(][cC][)]|\xa9|&#169;)? *([^ ].*[^-0-9, ]).*')

def normalize_text(t):
    return re.sub(b' +', b' ', t.replace(b'\n', b' ').replace(b'//', b'').replace(b'<br>', b'').replace(b'<p>', b'').replace(b'</p>', b'').replace(b'#', b'').replace(b'*', b'').replace(b'/', b'').replace(b'~', b''))

def find_license_text(fname):
    with open(fname, 'rb') as fin:
        content = fin.read()
        #lines = fin.readlines()
        #content = b"".join(lines[:30] + lines[-30:])
        content = normalize_text(content)

        for lname, lic_re in LIC_RES.items():
            if lic_re.search(content):
                FILES[fname]['license'] = lname
                return True
        else:
            for idx, other_lic in enumerate(OTHER_LICS):
                if other_lic in content:
                    FILES[fname]['license'] = 'LIC{}'.format(idx)
                    return True
            else:
                #print(fname, content)
                return False

def find_copyright_text(fname):
    with open(fname, 'rb') as fin:
        line_num = 0
        for line in fin:
            if line_num == 20:
                break
            line_num += 1
            line = line.strip()
            line = normalize_text(line)
            match = COPYRIGHT_RE.match(line)
            if match:
                #print("{:100}: years {:20} holder {}".format(line.decode(errors="ignore"), match.group(2).decode(errors="ignore"), match.group(3).decode(errors="ignore")))
                FILES[fname]['copyright'].append((match.group(2).decode(errors="ignore"), match.group(3).decode(errors="ignore")))
            else:
                match = COPYRIGHT2_RE.match(line)
                if match:
                    #print("{:100}: years {:20} holder {}".format(line.decode(errors="ignore"), match.group(3).decode(errors="ignore"), match.group(2).decode(errors="ignore")))
                    FILES[fname]['copyright'].append((match.group(3).decode(errors="ignore"), match.group(2).decode(errors="ignore")))
                else:
                    match = COPYRIGHT3_RE.match(line)
                    if match:
                        #print("{:100}: years {:20} holder {}".format(line.decode(errors="ignore"), "N/A", match.group(2).decode(errors="ignore")))
                        FILES[fname]['copyright'].append((None, match.group(2).decode(errors="ignore")))
                    else:
                        if TRIVIAL_COPYRIGHT_RE.match(line):
                            #print("Found {:100}, but could not make sense of it".format(line.decode(errors="ignore")))
                            pass

def main():
    mime_magic = magic.Magic(mime=True)
    succ_num = 0
    unsucc_num = 0
    ignored_num = 0
    total_num = 0
    for line in sys.stdin:
        if total_num % 2500 == 0:
            print(total_num)
        total_num += 1
        fname = line.strip()
        FILES[fname] = {'copyright': []}
        bname = os.path.basename(fname)
        ext = bname.split('.')[-1]

        if os.stat(fname).st_size == 0:
            FILES[fname]['license'] = 'empty'
            FILES[fname]['copyright'].append(None)
            continue

        if ext in ['c', 'cpp', 'h', 'hpp', 'ipp', 'tcc', 'cxx', 'txt', 'html', 'htm', 'Jamfile', 'v2', 'qbk', 'dimacs']:
            find_license_text(fname)
            find_copyright_text(fname)
            continue

        #print(fname, ext)
        mag = mime_magic.from_file(fname)
        if mag.split('/')[0] == 'text':
            find_license_text(fname)
            find_copyright_text(fname)
            continue

        #print(fname, mag)
        if mag in ['image/gif', 'image/png', 'image/jpeg', 'application/pdf', 'image/svg+xml']:
            print(fname, mag)

    print("\nSummary")
    print("I have seen {} files".format(len(FILES)))
    print("I found a license for {} of them".format(len([x for fname, x in FILES.items() if 'license' in x])))
    print("I found copyright holders for {} of them".format(len([x for fname, x in FILES.items() if len(x['copyright']) > 0])))

if __name__ == '__main__':
    main()
