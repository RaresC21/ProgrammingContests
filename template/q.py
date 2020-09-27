
# import numpy as np

# def f1(w1, w2):
#     w2 *= 2
#     a = np.exp(w1)
#     b = np.exp(w2)


#     return np.exp(a + b) + np.sin(a + b)

# def f2(w1, w2):
#     return w1 * w2 + 1.0 / (1 + np.exp(-w1))


# def f(w1, w2):
#     return (f1(w1, w2), f2(w1, w2))

# delta = 0.01
# # print((f(1 + delta, 2)[0] - f(1, 2)[0]) / delta)
# print((f(1 + delta, 2)[1] - f(1, 2)[1]) / delta)

\documentclass[12pt]{article}
\usepackage[utf8]{inputenc}

\usepackage{amsfonts} % use math symbols. Sets of Natural, Complex, numbers etc.
\usepackage{amsmath, mathtools}
\usepackage{amssymb}
\usepackage{listings} % for inserting code
\usepackage{color}
\usepackage{hyperref} % links to websites
\usepackage[margin=0.75in]{geometry}

\usepackage{enumerate}   % enumerate by a, b, c,...
\usepackage{tcolorbox}
\usepackage{tikz}
\usetikzlibrary {positioning}
\usetikzlibrary{arrows}

\newcommand{\QED} { \begin{flushright}                          % Q.E.D.
                        {\bfseries Q.E.D.}
                    \end{flushright} }

\newcommand{\cntr}[1]{\begin{center} #1 \end{center}}           %CENTER
\newcommand{\topic}[1]{\cntr{\bfseries #1}}
\newcommand{\problem}[1]{\begin{flushleft} \textbf{Problem #1:} \end{flushleft}}
\newcommand{\solution}{\begin{flushleft} \underline{\emph{Solution:}} \end{flushleft}}
\newcommand{\paren}[1]{\left( #1 \right)}
\newcommand{\R}[0]{\mathbb{R}}
\newcommand{\norm}[1]{\left\lVert#1\right\rVert}
\newcommand{\inprod}[1]{\langle#1\rangle}

\newcommand{\case}[3]{                                          % CASE
            \textit{Case #1:} #2
            \begin{quote} #3 \end{quote}}
\newcommand{\scase}[3]{                                          % SUB CASE
            \textit{Subcase #1:} #2
            \begin{quote} #3 \end{quote}}

\newcommand{\conj}[1]{ {\overline{#1}} }

%%%%%%%%%       PARAGRAPH INFO
\setlength{\parskip}{0em}

%%%%%%%%%       TITLE
\title{Deep Learning HW1 \vspace{-0.5cm}}
\author{Rares Cristian}
\date{26 September 2019}
\pagenumbering{gobble}

%%%%%%%%%%%%%%%%           CODE

\definecolor{dkgreen}{rgb}{0,0.6,0}
\definecolor{gray}{rgb}{0.5,0.5,0.5}
\definecolor{mauve}{rgb}{0.58,0,0.82}

\lstset{frame=tb,
  language=Java,
  aboveskip=3mm,
  belowskip=3mm,
  showstringspaces=false,
  columns=flexible,
  basicstyle={\small\ttfamily},
  numbers=none,
  numberstyle=\tiny\color{gray},
  keywordstyle=\color{blue},
  commentstyle=\color{dkgreen},
  stringstyle=\color{mauve},
  breaklines=true,
  breakatwhitespace=true,
  tabsize=3
}

\begin{document}

\maketitle

% \begin{center}
% \textbf{Differential Geometry Homework 1} \\ Rares Cristian
% \end{center}

\problem{1}

Consider the following

\[ \arg\min f(w^{(t)}) + \inprod{w - w^{(t)}, \nabla f(w^{(t)})} + \frac{\lambda}{2}  \norm{w - w^{(t)}}^2 \]

What is the solution $w^{*}$ of the above optimization? What does that tell you about the gradient descent update rule? What is the relationship between $\lambda$ and $\eta$?. Recall the gradient descent update rule is

\[ w^{(t+1)} = w^{t} - \eta \nabla f(w^{(t)}) \]

\solution

To find the minimum $w^*$ for the expression above, we can find the zeros of the its gradient (note that the function is convex). The terms $f(w^{(t)}$, $w^{(t)}$, $\nabla f(w^{(t)})$ are constant with respect to $w$, so we easily find that the gradient is simply

\[ \nabla f(w^{(t)}) + \lambda (w - w^{(t)} \]

Setting the above equal to zero, we find that the minimum is achieved at

\[ w^* = w^{(t)} - \frac{1}{\lambda} \nabla f(w^{(t)}) \]

Hence, $\eta = \frac{1}{\lambda}$.

\newpage
\problem{2}

Consider a sequence of vectors $v_1, v_2, \dots, v_T$, and an upadate equation of the form $w^{(t)} = w^{(t-1)} - \eta v_{(t-1)}$. with $w^{(1)} = 0$. Show that for any $w^*$,

\[ \sum_{t=1}^T \inprod{w^{(t)} - w^*, v_t} \leq \frac{\norm{w^*}^2}{2\eta} + \frac{\eta}{2} \sum_{t=1}^T \norm{v_t}^2 \]

\solution

We can rewrite $ \inprod{w^{(t)} - w^*, v_t} =  \inprod{w^{(t)}, v_t} -  \inprod{w^*, v_t}$. Looking at the left term, using the update rule once we find $ \inprod{w^{t}, v_t} = \inprod{w^{(t - 1)}, v_t} - \eta \inprod{v_{t-1}, v_t} $. Using the rule repeatedly, we find

\[ \inprod{w^{t}, v_t} = \inprod{w^{(1)}, v_t} - \eta \sum_{k=1}^t \inprod{v_k, v_t} \]

Since $w^{(1)} = 0$, this is

\[ \inprod{w^{t}, v_t} = - \eta \sum_{k=1}^t \inprod{v_k, v_t} \]

Now, back to the original summation,

\[ \sum_{t=1}^T \inprod{w^{(t)} - w^*, v_t} = -\eta \sum_{1 \leq i < k \leq T} \inprod{v_i, v_k} - \sum_{t=1}^T \inprod{w^*, v_t}\]

Note that the left summation is a sum of inner products of all pairs of vectors from $v_1, \dots, v_T$. Now, consider rewriting the above as

\[ -\eta \sum_{1 \leq i < k \leq T} \inprod{v_i, v_k} - \eta \sum_{t=1}^T \inprod{\frac{1}{\eta}w^*, v_t}  \]

Now, we have a sum of inner products of all pairs of vectors from $v_1, \dots, v_T,$ and $\frac{w^*}{\eta}$ (scaled by $-\eta$). With this in mind, we claim that for any vectors $x_1, \dots, x_n$,

\[ - \sum_{1 \leq i < k \leq n} \inprod{x_i, x_k} \leq \frac{1}{2} \sum_{t=1}^n \norm{x_i}^2 \]

Indeed, consider

\begin{align*}
    0 \leq \norm{x_1 + \dots + x_n}^2 =&\ \inprod{x_1 + \dots + x_n, x_1 + \dots + x_n} \\
      =&\ \sum_{i=1}^n\sum_{i=1}^n \inprod{x_i, x_k} \\
      =&\ \sum_{t=1}^n \inprod{x_i, x_i} + 2 \sum_{1 \leq i < k \leq n} \inprod{x_i, x_k}
\end{align*}

Hence $0 \leq \sum_{t=1}^n \norm{x_i}^2 + 2 \sum_{1 \leq i < k \leq n} \inprod{x_i, x_k} $ proving the claim. Using this inequality on the list $v_1, \dots, v_T, \frac{1}{\eta}w^*$ we find that

\[ -\eta \paren { \sum_{1 \leq i < k \leq T} \inprod{v_i, v_k} + \sum_{t=1}^T \inprod{\frac{1}{\eta}w^*, v_t} } \leq \eta \paren{ \frac{1}{2} \sum_{t=1}^T\norm{x_t}^2 + \frac{\norm{w^*}^2}{2\eta^2}} \]

thus solving the problem.

\newpage
\problem{3}

Now let’s start putting things together and analyze the convergence rate of gradient descent. First, show that for $\conj{w} = \frac{1}{T}\sum_{t=1}^Tw^{(t)}$

\[ f(\conj{w}) - f(w^*) \leq \frac{1}{T} \sum_{t=1}^T \inprod{w^{(t)} - w^*, \nabla f(w^{(t)}} \]

Next, use the result from part 2 with upper bounds $B$ and $\rho$ for $\norm{w^*}$ and $\norm{\nabla f(w^{(t)})}$ respectively and show that for fixed $\eta = \sqrt{B^2 / (\rho^2T)}$, the convergence rate of gradient descent is $O(1 / \sqrt{T})$.

\solution

Since $f$ is convex, we have the following first-order lower bound for any $w$,

\[ f(w) \geq f(w^{(t)} + \inprod{w - w^{(t)}, \nabla f(w^{(t)}} \]

Using $w^*$ in place of $w$ and summing over all $t = 1, \dots, T$, we have

\[ \sum_{t=1}^T f(w^*) \geq \sum_{t=1}^T f(w^{(t)}) + \sum_{t=1}^T \inprod{w^* - w^{(t)}, \nabla f(w^{(t)}}  \]

Rearranging terms and noting that $\sum_{t=1}^T f(w^*) = Tf(w^*)$, we find

\[ \frac{1}{T} \sum_{t=1}^T f(w^{(t)}) - f(w^*) \leq \frac{1}{T}\sum_{t=1}^T \inprod{w - w^{(t)}, \nabla f(w^{(t)}} \]

By Jensen's inequality,

\[ f(\conj{w}) = f\paren{\frac{1}{T} \sum_{t=1}^Tw^{(t)} } \leq \frac{1}{T} \sum_{t=1}^T f(w^{(t)})  \]

Using this in combination with the previous inequality proves the claim that

\[ f(\conj{w}) - f(w^*) \leq \frac{1}{T} \sum_{t=1}^T \inprod{w^{(t)} - w^*, \nabla f(w^{(t)}} \]

Now, we can use the inequality from part 2, letting $v_t = \nabla f(w^{(t)})$:

\[ f(\conj{w}) - f(w^*) \leq \frac{1}{T} \paren{ \frac{\norm{w^*}^2}{2\eta} + \frac{\eta}{2} \sum_{t=1}^T \norm{\nabla f(w^{(t)})}^2 } \]

Using the upper bounds $B$ and $\rho$ for $\norm{w^*}$ and $\norm{\nabla f(w^{(t)})}$,

\[ f(\conj{w}) - f(w^*) \leq \frac{1}{T} \paren{ \frac{B^2}{2\eta} + \frac{\eta}{2} \sum_{t=1}^T \rho^2 } = \paren{ \frac{B^2}{2T\eta}} + \frac{\eta\rho^2}{2} \]

Substituting $\eta = \sqrt{B^2 / (\rho^2T)}$,

\[ f(\conj{w}) - f(w^*) \leq \frac{B\rho \sqrt{T}}{2T} + \frac{B\rho}{2\sqrt{T}} = O\paren{\frac{1}{\sqrt{T}}} \]


\newpage
\problem{4}

Consider an objective function comprised of $N = 2$ terms:

\[ f(w) = \frac{1}{2}(w - 2)^2 + \frac{1}{2}(w + 1)^2 \]

Now consider using SGD (with a batch size of $B = 1$) to minimize this objective. Specifically, in each iteration, we will pick one of the two terms (uniformly at random), and take a step in the direction of the negative gradient, with a constant step-size of $\eta$. You can assume $\eta$ is small enough that every update does result in improvement on the sampled term. Is SGD guaranteed to decrease the overall loss function in every iteration? If no, provide a counter-example.

\solution

No. Suppose that $w^{(t)} = 0$ and that we are currently looking only at the term $\frac{1}{2}(w + 1)^2$. The gradient is simply $(w^{(t)} + 1)$. A step of gradient descent would give us

\[ w^{(t+1)} = w^{(t)} - \eta(w^{(t)} + 1) = -\eta \]

The initial cost was

\[ f(w^{(t)}) = f(0) = \frac{1}{2} (2^2 + 1^2) = \frac{1}{2} \cdot 5 \]

while the cost after an iteration is now

\[ f(w^{(t+1)} = f(-\eta) = \frac{1}{2} ((-\eta - 2)^2 + (-\eta + 1)^2) = \frac{1}{2}(2\eta^2 + 2\eta + 5) \]

Since $\eta > 0$, we have $f(w^{(t+1)}) > f(w^{(t)})$. Hence, we do not decrease the overall loss function in every iteration.

\newpage
\problem{5}

\begin{enumerate}[a)]
    \item

    $f((1, 2)) \approx (7.8 \cdot 10^{24}, 2.73)$

\begin {tikzpicture}[-latex ,auto ,node distance = 2.5 cm and 2.5 cm, on grid, semithick,
vertex/.style={circle,draw,minimum size=1em},
edge/.style={->,> = latex'},
state/.style ={ circle, top color = white, draw, blue, text = blue,
minimum width = 0.1 cm}]
\node[state, opacity = 1] (A) {$w_2$};
\node[state, opacity = 1] (B) [above = of A] {$w_1$};
\node[state] (C) [right = of A] {$ * 2$};
\node[state] (D) [right = of C] {$e^x$};
\node[state] (E) [right = of B] {$e^x$};
\node[state] (F) [right = of E] {+};
\node[state] (H) [right = of F] {$e^x$};
\node[state] (G) [below = of H] {sin};
\node[state] (I) [right = of H] {+};
\node[state, opacity = 0] (F1) [right = of I] {};

\path[->] (A) edge node{} (C) ;
\path[->] (C) edge node{$y_1$} (D) ;
\path[->] (B) edge node{} (E) ;
\path[->] (E) edge node{$y_2$} (F) ;
\path[->] (D) edge node{$y_3$} (F) ;
\path[->] (F) edge node{$y_4$} (H) ;
\path[->] (F) edge node{$y_4$} (G) ;
\path[->] (G) edge node{$y_5$} (I) ;
\path[->] (H) edge node{$y_6$} (I) ;
\path[->] (I) edge node{$f_1(w_1, w_2)$} (F1) ;


\node[state] (K) [above = of E] {*};
\node[state] (L) [above = of K] {$e^{-x}$};
\node[state] (M) [right = of L] {+1};
\node[state] (N) [right = of M] {$\frac{1}{x}$};
\node[state] (O) [below = of N] {+};
\node[state, opacity = 0] (F2) [right = of O] {};

\path[->] (A) edge node{} (K) ;
\path[->] (B) edge node{} (K) ;
\path[->] (B) edge node{} (L) ;
\path[->] (L) edge node{$x_1$} (M) ;
\path[->] (M) edge node{$x_2$} (N) ;
\path[->] (N) edge node{$x_3$} (O) ;
\path[->] (K) edge node{$x_4$} (O) ;
\path[->] (O) edge node{$f_2(w_1, w_2)$} (F2) ;

\end{tikzpicture}

\newpage
\item

\begin{align*}
    \frac{\partial f_1}{\partial w_1} \approx&\ \frac{f_1(w_1 + \Delta, w_2) - f_1(w_1, w_2)}{\Delta} = 2.16 \cdot 10^{25} \\ \\
    \frac{\partial f_1}{\partial w_2} \approx&\ \frac{f_1(w_1, w_2 + \Delta) - f_1(w_1, w_2)}{\Delta} = 1.57 \cdot 10^{27} \\ \\
    \frac{\partial f_2}{\partial w_1} \approx&\ \frac{f_2(w_1  + \Delta, w_2) - f_2(w_1, w_2)}{\Delta} = 2.20 \\ \\
    \frac{\partial f_2}{\partial w_2} \approx&\ \frac{f_2(w_1, w_2 + \Delta) - f_2(w_1, w_2)}{\Delta} = 1
\end{align*}

\newpage
\item



\begin{align*}
    \frac{\partial y_1}{\partial w_2} =&\ 2 \\ \\
    \frac{\partial y_3}{\partial w_2} =&\ \frac{\partial y_3}{\partial y_1} \frac{\partial y_1}{\partial w_2} = 2e^{y_1} = 2e^{2w_2} \\ \\
    \frac{\partial y_4}{\partial w_2} =&\ \frac{\partial y_4}{\partial y_3} \frac{\partial y_3}{\partial w_2} = 1 \cdot 2e^{2w_2} \\ \\
    \frac{\partial y_5}{\partial w_2} =&\ \frac{\partial y_5}{\partial y_4} \frac{\partial y_4}{\partial w_2} = \cos(y_4) 2e^{2w_2} = \cos(e^{w_1} + e^{2w_2}) \cdot 2e^{2w_2} \\ \\
    \frac{\partial y_6}{\partial w_2} =&\ \frac{\partial y_6}{\partial y_4} \frac{\partial y_4}{\partial w_2} = e^{y_4} 2e^{2w_2} = e^{e^{w_1} + e^{2w_2}} 2e^{2w_2} \\ \\
    \Aboxed{
    \frac{\partial f_1}{\partial w_2} =&\
    \frac{\partial f_1}{\partial y_6} \frac{\partial y_6}{\partial w_2} +  \frac{\partial f_1}{\partial y_5} \frac{\partial y_5}{\partial w_2} = e^{e^{w_1} + e^{2w_2}} 2e^{2w_2} + \cos(e^{w_1} + e^{2w_2}) \cdot 2e^{2w_2} }  \\ \\
    \frac{\partial y_2}{\partial w_1} =&\ e^{w_1} \\ \\
    \frac{\partial y_4}{\partial w_1} =&\ \frac{\partial y_4}{\partial y_2} \frac{\partial y_2}{\partial w_1} = e^{w_1} \\ \\
    \frac{\partial y_6}{\partial w_1} =&\
    \frac{\partial y_6}{\partial y_4} \frac{\partial y_4}{\partial w_1} = e^{y_4} e^{w_1} = e^{e^{w_1} + e^{2w_2}} e^{w_1} \\ \\
    \frac{\partial y_5}{\partial w_1} =&\ \frac{\partial y_5}{\partial y_4} \frac{\partial y_4}{\partial w_1} = \cos(y_4) e^{w_1} = \cos({e^{w_1} + e^{2w_2}}) e^{w_1} \\ \\
    \Aboxed{\frac{\partial f_1}{\partial w_1} =&\ \frac{\partial f_1}{\partial y_6} \frac{\partial y_6}{\partial w_1} + \frac{\partial f_1}{\partial y_5} \frac{\partial y_5}{\partial w_1} = \cos({e^{w_1} + e^{2w_2}}) e^{w_1} + e^{e^{w_1} + e^{2w_2}} e^{w_1}}  \\
    \end{align*}
    \newpage

\begin{align*}
    \frac{\partial x_4}{\partial w_2} =&\  w_1 \\ \\
    \Aboxed{\frac{\partial f_2}{\partial w_2} =&\ \frac{\partial f_2}{\partial x_4} \frac{\partial x_4}{\partial w_2} = w_1 } \\ \\
    \frac{\partial x_4}{\partial w_1} =&\  w_2 \\ \\
    \frac{\partial x_1}{\partial w_1} =&\  -e^{-w_1} \\ \\
    \frac{\partial x_2}{\partial w_1} =&\
    \frac{\partial x_2}{\partial x_1} \frac{\partial x_1}{\partial w_1} = -e^{-w_1} \\ \\
    \frac{\partial x_3}{\partial w_1} =&\  \frac{\partial x_3}{\partial x_2} \frac{\partial x_2}{\partial w_1} = \frac{-1}{x_2^2} \cdot (-e^{-w_1}) = \frac{e^{-w_1}}{(1 + e^{-w_1})^2} \\ \\
    \Aboxed{\frac{\partial f_2}{\partial w_1} =&\ \frac{\partial f_2}{\partial x_4} \frac{\partial x_4}{\partial w_1} + \frac{\partial f_2}{\partial x_3} \frac{\partial x_3}{\partial w_1} = w_2 + \frac{e^{-w_1}}{(1 + e^{-w_1})^2} }
\end{align*}



\end{enumerate}

\newpage
\problem{6}

If $G$ is a directed acyclic graph, then $G$ has a topological ordering.

\solution

We will generate the topological ordering as follows. Since $G$ is a DAG, there exists a node, $v_1$, with no incoming edges. Place this node first in the ordering. Clearly, no matter the rest of the ordering, there will be no edge from some later node going into $v_1$. Remove node $v_1$ from $G$. The result is still a DAG (we removed a node, and edges adjacent to it, so there is no way we could have formed a cycle). This graph again has some node with no incoming edges. Place this node next in the ordering, after $v_1$.

Continue this process until we have removed each node. Every time we add a node to the ordering, we are guaranteed that the topological property holds - there can be no nodes from it going into a node already on the list since that would contradict the fact that each time we add a node, it has no incoming edges from the remaining nodes in the graph.

\newpage
\problem{7}

If a graph $G$ has a topological ordering, prove that $G$ is a DAG.

\solution

For the sake of contradiction, suppose that $G$ is not a DAG. Then, $G$ contains a cycle, say $v_1 \to v_2, \to \dots \to v_k \to v_1$. We must have that $v_1$ comes before $v_2$ in the ordering, since we have a $(v_1, v_2)$ edge. Similarly, we must have $v_i$ before $v_{i+1}$ for $i = 1\dots k-1$. Hence, $v_1$ comes before $v_k$ in the ordering. However, we also have the edge $(v_k, v_1)$ implying that the ordering is not topological, a contradiction. Hence, $G$ must be a DAG.

\end{document}



