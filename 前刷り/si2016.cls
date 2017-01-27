%
% pLaTeX2e 山彦シンポジウム予稿用クラスファイル
%
% by aokaze (HARA Yoshitaka ： hara.y@roboken.esys.tsukuba.ac.jp)
%
\typeout{*** Manuscript Style for pLaTeX2e by aokaze ***}

% 新ドキュメントクラス
% http://oku.edu.mie-u.ac.jp/~okumura/jsclasses/
\LoadClassWithOptions{jsarticle}

%\usepackage[dvips]{graphicx}
\usepackage{amsmath}
\usepackage{amsthm}
\usepackage{amssymb}
\usepackage[T1]{fontenc}
\usepackage{mathptmx}  %% 新版
% \usepackage{mathptm}  %% 旧版（mathptmx が未インストールの場合）
\usepackage{pifont}
\usepackage{bm}  %% 数式用ボールド
\usepackage{float}  %% [H]  here.sty の後継
\usepackage{multirow}  %% 表の縦二段をつなげる
\usepackage{subfigure}
\usepackage{tabularx}
\usepackage{url}
% \usepackage{cite}  %% 参考文献 [1,2,3] を [1-3] に
% \usepackage{jumoline}  %% 取り消し線
\usepackage{layout}

% センタリングしたセクション
% \newcommand{\csection}[1]{{\centering\section{#1}}}

% 脚注を *1) に
\renewcommand\thefootnote{*\kern1pt\arabic{footnote})\;\;}

% 箇条書きの形式を 1. から 1) に
\renewcommand{\labelenumi}{\theenumi)}

% subfigure 関連
\renewcommand{\subfigtopskip}{0pt}
\renewcommand{\subfigcapskip}{-6pt}  %% 図と subfigure のキャプションの間隔
\renewcommand{\subfigcaptopadj}{0pt}
\renewcommand{\subfigbottomskip}{0pt}  %% キャプションとサブキャプションの間隔
\renewcommand{\subfigcapmargin}{0pt}
\renewcommand{\subfiglabelskip}{0pt}

% 図、表を思い通りの位置に
\renewcommand{\topfraction}{1.00}
\renewcommand{\bottomfraction}{1.00}
\renewcommand{\textfraction}{0.00}
\renewcommand{\floatpagefraction}{1.00}
\renewcommand{\dbltopfraction}{1.00}
\renewcommand{\dblfloatpagefraction}{1.00}
%
\setcounter{topnumber}{10}
\setcounter{bottomnumber}{10}
\setcounter{totalnumber}{20}

% ページ余白関連（A4：210 mm × 297 mm、1 インチ = 25.4 mm）
% http://www.nsknet.or.jp/~tony/TeX/faq/layout.htm
\setlength{\voffset}{-5.4truemm}

\setlength{\topmargin}{0.0truemm}
\setlength{\textheight}{250truemm}
\setlength{\headheight}{10truemm}
\setlength{\headsep}{-10truemm}
\setlength{\hoffset}{0.0truemm}

\setlength{\oddsidemargin}{-10.4truemm}
\setlength{\evensidemargin}{-10.4truemm}
\setlength{\textwidth}{180truemm}
\setlength{\columnsep}{8truemm}

% 行間
% 14pt＝4.5mm
\setlength{\baselineskip}{20pt}
%\setlength{\baselineskip}{4.0truemm}

% ページ番号なし
\pagestyle{empty}

% 日付リセット
\date{}

% タイトル
\def\title#1{\gdef\@title{#1}}
\def\author#1{\gdef\@author{#1}}
\def\engtitle#1{\gdef\@engtitle{#1}}
\def\engauthor#1{\gdef\@engauthor{#1}}
\def\organization#1{\gdef\@organization{#1}}
\def\keyword#1{\gdef\@keyword{#1}}
\def\and{%%   % \begin{tabular}
  \end{tabular}%
  \hskip 1zw plus .01fil%
  \begin{tabular}[t]{c}%% \end{tabular}
  }
\def\@maketitle{\newpage%
  \null%
  \begin{center} %
%   \vspace*{5mm} %
   \vspace*{0mm} %
    {\LARGE\bf \@title \par } %
    \@ifundefined{@engtitle}{}{%
    \vskip 0.5em
    {\large \@author}%
    \@ifundefined{@engauthor}{}{%
    \vskip 1.0em
    {\LARGE \@engtitle}
    \gdef\@engtitle{}}%
    \vskip 0.5em
    {\large \@engauthor}
    \gdef\@engauthor{}}%
    \@ifundefined{@organization}{}{%
    \vskip 0.5em
    {\large \@organization}
%    {\@organization}
    \gdef\@organization{}}%
    \vskip 1.0em
  \end{center}%
  \@ifundefined{@abstract}{}{%
    \small%
    \begin{center}%
      \begin{minipage}{.9\textwidth}%
      \vspace*{0mm} %
      {Abstract:}\@abstract%
      \end{minipage}%
    \end{center}%
    \gdef\@abstract{}}%
%   \vspace*{0.0mm} %
%   \vspace*{-4.0mm} %
  \@ifundefined{@keyword}{}{%
    \small%
    \begin{center}
      \begin{minipage}{.9\textwidth}%
      {\bf Keywords: }\@keyword%
      \end{minipage}
    \end{center}
    \gdef\@keyword{}}%
%   \vspace*{5.0mm} %
   \vspace*{0mm} %
%    \hbox{\kern .3\textwidth\vbox{\hrule width .4\textwidth}}%
    \vskip 1zh}%
\long\def\abstract#1{\long\gdef\@abstract{#1}}%

% フォント
\renewcommand{\headfont}{\bfseries}

% セクション
\renewcommand{\thesection}{\presectionname\@arabic\c@section.\postsectionname}
\if@twocolumn
  \renewcommand{\subsection}{\@startsection{subsection}{2}{\z@}%
    {0.4\Cvs}{0.2\Cvs}%
    {\normalfont\normalsize\headfont}}
  \renewcommand{\subsubsection}{\@startsection{subsubsection}{3}{\z@}%
    {0.2\Cvs}{\z@}%
    {\normalfont\normalsize\headfont}}
\fi

% 図、表のキャプション
\renewcommand{\figurename}{Fig.~}
\renewcommand{\tablename}{Table ~}
\def\fnum@figure{\headfont\figurename\nobreak\thefigure\normalfont}
\def\fnum@table{\headfont\tablename\nobreak\thetable\normalfont}

\renewcommand{\appendix}{\par
  \setcounter{section}{0}%
  \setcounter{subsection}{0}%
  \gdef\presectionname{\appendixname}%
  \gdef\postsectionname{}%
  \gdef\thesection{\presectionname\@Alph\c@section.\postsectionname}%
  \gdef\thesubsection{\@Alph\c@section.\@arabic\c@subsection}}

% ヘッダをページ右上に
\def\ps@myheadings{\def\@oddhead{\hbox{}\hfil\rightmark
}\def\@oddfoot{}\def\@evenhead{
\thepage\hfil\leftmark\hbox
{}}\def\@evenfoot{}\def\sectionmark##1{}\def\subsectionmark##1{}}

\makeatletter



\def\Kana#1{\expandafter\@Kana\csname c@#1\endcsname}

\def\@Kana#1{%

  \ifcase#1\or １\or ２\or ３\or ４\or

               ５\or ６\or ７\or ８\or ９\or

               １０\or １１\or １２\or １３\or １４\or

               １５\or １６\or １７\or １８\or １９\or

               ２０\or ２１\or ２２\or ２３\or ２４\or

               ２５\or ２６\or ２７\or ２８\or ２９\or

               ３０\or ３１\or ３２\or ３３\or ３４\or

               ３５\or ３６\or ３７\or ３８\or ３９\or

               ４０\or ４１\or ４２\or ４３\or ４４\or

               ４５\or ４６\or ４７\or ４８\or ４９\or

               ５０\or ５１\or ５２\or ５３\or ５４\or

               ５５\or ５６\or ５７\or ５８\or ５９\or

               ６０\or ６１\or ６２\or ６３\or ６４\or

               ６５\or ６６\or ６７\or ６８\or ６９\or

               ７０\or ７１\or ７２\or ７３\or ７４\or

               ７５\or ７６\or ７７\or ７８\or ７９\or

               ８０\or ８１\or ８２\or ８３\or ８４\or

               ８５\or ８６\or ８７\or ８８\or ８９\or

               ９０\or ９１\or ９２\or ９３\or ９４\or

               ９５\or ９６\or ９７\or ９８\or ９９\or １００ \or

                \else\@ctrerr\fi}



\makeatother%% プリアンブルで定義する場合は必須




\renewcommand{\thesection}{\Kana{section}.}
\renewcommand{\thesubsection}{\thesection\Kana{subsection}.}
\renewcommand{\thesubsubsection}{\thesubsection\Kana{subsubsection}}
