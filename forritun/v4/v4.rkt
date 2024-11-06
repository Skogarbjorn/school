;; Notkun: (myiota n)
;; Fyrir: n er heiltala, n>=0
;; Gildi: Listi allra heiltalna i, þannig að
;; 0 < i <= n, í vaxandi röð,
;; þ.e. listinn (1 2 ... n)
(define (myiota n)
;; Notkun: (hjalp r x)
;; Fyrir: r er heiltala, 0 <= r <= n.
;; x er listinn (r+1 r+2 ... n)
;; Gildi: Listinn (1 2 ... n)
(define (hjalp r x)
  (if (= r 0)
      x
      (hjalp (- r 1) (cons r x))
      )
)
(hjalp n '())
)
(myiota 0)
(myiota 1)
(myiota 5)



;; Notkun: (myfoldl f u x)
;; Fyrir: f er tvíundarfall, þ.e. fall
;; sem tekur tvö viðföng af einhverju
;; tagi, x er listi (x1 ... xN)
;; gilda af því tagi, u er gildi
;; af því tagi.
;; Gildi: (f (f ...(f (f u x1) x2) ...) xN)
;; Aths.: Með öðrum orðum, ef við skilgreinum
;; tvíundaraðgerð ! með a!b = (f a b),
;; þá er útkoman úr fallinu gildið á
;; u ! x1 ! x2 | ... ! xN
;; þar sem reiknað er frá vinstri til
;; hægri
(define (myfoldl f u x)
  (if (null? x)
      u
      (myfoldl f (f u (car x)) (cdr x))
  )
)
(myfoldl - 3 '(1 2))
(myfoldl (lambda (a b) (cons b a)) '() '(1 2 3))

(myfoldl + 0 (myiota 30))
(myfoldl * 1 (myiota 30))

;;EINSTAKLINGSVERKEFNI

;; Notkun: (sum1 n)
;; Fyrir: n er heiltala, n>=0
;; Gildi: Summan 0+1+...+n
(define (sum1 n)
  (define (sum1help n total)
    (if (= n 0)
        total
        (sum1help (- n 1) (+ total n))
    )
    )
  (sum1help n 0)
  )
(sum1 6)
(sum1 0)

;; Notkun: (sum2 i n)
;; Fyrir: i og n eru heiltölur, i <= n+1
;; Gildi: Summan i+(i+1)+...+n, summa þeirra
;; heiltalna k þannig að i <= k <= n.
(define (sum2 i n)
  (define (sum2help i n total)
    (if (= i (+ n 1))
        total
        (sum2help (+ i 1) n (+ i total))
        )
    )
   (sum2help i n 0)
  )
(sum2 11 10)
(sum2 3 10)



;; Notkun: ((sum3 i) n)
;; Fyrir: i og n eru heiltölur, i <= n+1
;; Gildi: Summan i+(i+1)+...+n
(define (sum3 i)
  (lambda (x) (if (= i (+ x 1)) 0 (+ i ((sum3 (+ i 1)) x))))
  )

((sum3 11) 10)
((sum3 3) 10)

;; Notkun: (reviota n)
;; Fyrir: n er heiltala n >= 0
;; Gildi: (n n-1 ... 2 1)
(define (reviota n)
  ;; Notkun: (helper m l)
  ;; Fyrir: m er heiltala 0 < m <= n+1, l er listi
  ;; Gildi: (n n-1 ... m+1 m)
  (define (helper m l)
    (if (= m (+ n 1))
        l
        (helper (+ m 1) (cons m l))
        )
    )
  (helper 1 '())
  )
(reviota 10)
(reviota 0)





