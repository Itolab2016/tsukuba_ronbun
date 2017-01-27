%
% pLaTeX2e 卒業論文クラスファイル
%
% by Kouhei (ITO Kouhei ： kouhei.ito@itolab-ktc.com)
%
\typeout{*** Manuscript Style for pLaTeX2e by kouhei ***}

% 新ドキュメントクラス
% http://oku.edu.mie-u.ac.jp/~okumura/jsclasses/
\LoadClassWithOptions{jsbook}
\usepackage[dvipdfmx]{graphicx}
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
%\usepackage{layout}
\usepackage{fancyhdr}

\pagestyle{fancy}
\lhead[]{}
\chead[]{}
\rhead[]{}
\lfoot[]{}
\cfoot[\thepage]{\thepage}
\rfoot[]{}
\renewcommand{\headrulewidth}{0pt}
\renewcommand{\footrulewidth}{0pt}


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
\setlength{\topmargin}{-2truemm}
\setlength{\textheight}{253truemm}
\setlength{\headheight}{0pt}
\setlength{\headsep}{0truemm}
\setlength{\oddsidemargin}{-4.4truemm}
\setlength{\evensidemargin}{-4.4truemm}
\setlength{\textwidth}{177truemm}
\setlength{\columnsep}{5truemm}

% 日付リセット
\date{}

% 図、表のキャプション
\renewcommand{\figurename}{図~}
\renewcommand{\tablename}{表~}
\def\fnum@figure{\headfont\figurename\nobreak\thefigure\normalfont}
\def\fnum@table{\headfont\tablename\nobreak\thetable\normalfont}


\makeatletter
\renewcommand{\chapter}{%
  \if@openright\cleardoublepage\else\clearpage\fi
  \global\@topnum\z@
  \secdef\@chapter\@schapter}
\makeatother
