#!/bin/bash

##############################################################################
# This file is part of RetroCRT (https://github.com/xovox/RetroCRT)
#
# RetroCRT is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# RetroCRT is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with RetroCRT.  If not, see <https://www.gnu.org/licenses/>.
##############################################################################

export rpie_onend_script_dir="$HOME/scripts/runcommand-onend.d"
export runcommand_onend_log="/dev/shm/runcommand-onend.log"
(
for rpie_onend_script in $rpie_onend_script_dir/*.{sh,pl,py} ; do
    if [ -f "$rpie_onend_script" ]; then
        echo "##############################################################################"
        echo "$rpie_onend_script"
        echo "##############################################################################"
        $rpie_onend_script "$1" "$2" "$3" "$4"
    fi
done
) > $runcommand_onend_log 2>&1
