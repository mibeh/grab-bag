#!/bin/bash                                                                                                                                                                                         USERNAMES=$(cat users)                                                                                                                                                                              for u in $USERNAMES; do                                                                                   echo "$u"                                                                                         useradd -m -s "/bin/bash" -d /home/"$u" "$u"                                                      echo "$u":"$u"123 | sudo chpasswd                                                                 echo user "$u" added with password "$u"123                                                        chage -d 0 $u                                                                             done     #!/bin/bash

USERNAMES=$(cat users)

for u in $USERNAMES; do
        echo "$u"
        useradd -m -s "/bin/bash" -d /home/"$u" "$u"
        echo "$u":"$u"123 | sudo chpasswd
        echo user "$u" added with password "$u"123
        chage -d 0 $u
done
