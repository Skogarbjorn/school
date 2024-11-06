#set page(width: 20cm, height: auto)
#set heading(numbering: "1.1")
= Hópverkefni
#set enum(numbering: "a)")

==
Svarið er *(B)* Mengi strengja.

==
=== BNF
+ `<R> ::= 'a' <R> 'c' | <B>` \
  `<B> ::= 'b' <B> |` $epsilon$

+ `<R> ::= <abpart> <cdpart>` \
  `<abpart> ::= 'ab' <abpart> |` $epsilon$ \
  `<cdpart> ::= 'c' <cdpart> 'd' |` $epsilon$

+ `Imposter`

+ `<R> ::= <abpart> <cpart>` \
  `<abpart> ::= 'a' <abpart> 'b' |` $epsilon$ \
  `<cpart> ::= 'c' <cpart> |` $epsilon$

=== EBNF

+ `R = 'a', R, 'c' | {'b'};`

+ `R = {'ab'}, cdpart;` \
  `cdpart = ['c', cdpart, 'd'];`

+ `Prob imposter líka`

+ `R = abpart, {'c'};` \
  `abpart = ['a', abpart, 'b'];`

=== Málrit

= Einstaklingsverkefni

==
